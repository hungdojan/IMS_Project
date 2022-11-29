#include <ncurses.h>
#include <string.h>
#include "board.h"

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

void init_setup() {
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    timeout(5);
    curs_set(0);
}


WINDOW *create_window(int h, int w, int y, int x) {
    WINDOW *local_win = newwin(h, w, y, x);
    return local_win;
}

void destroy(WINDOW *local_win) {
    wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(local_win);
    delwin(local_win);
}


int main() {
    WINDOW *my_win;
    struct board_t b = { 0, 0, NULL, NULL };
    if (init_board(&b, BOARD_WIDTH, BOARD_HEIGHT))
        goto err_board;

    int ch = 0;

    initscr();
    init_setup();

    int h = BOARD_HEIGHT+2;
    int w = BOARD_WIDTH;
    int y = (LINES - h) / 2;
    int x = (COLS - w) / 2;
    // int index = 0, c='a';
    int timer = 0;
    int timer_limit = 100;

    printw("%d, %d\n", h, w);
    refresh();

    my_win = create_window(h, w, y, x);
    display_board(&b, my_win);

    do {
        ch = getch();
        switch (ch) {
            case KEY_UP:
                timer_limit = MAX(0, timer_limit-5);
                break;
            case KEY_DOWN:
                timer_limit = MIN(100, timer_limit+5);
                break;
            case KEY_LEFT:
                timer_limit = MIN(100, timer_limit+1);
                break;
            case KEY_RIGHT:
                timer_limit = MAX(0, timer_limit-1);
                break;
            case ' ':
                timeout(-1);
        }
        if (timer < timer_limit) {
            timer++;
            continue;
        }

        update_board(&b);
        display_board(&b, my_win);
        timer = 0;
    } while (ch != 'q');

    endwin();
    destroy_board(&b);
    return 0;
err_board:
    return 1;
}

/* main.c */

