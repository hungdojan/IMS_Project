/**
 * @brief File containing starting point of the application.
 *
 * This source code serves as submission for
 * a project of class IMS at FIT, BUT 2022/23.
 *
 * @file main.c
 * @authors Hung Do (xdohun00)
 *          Marek Dohnal (xdohna48)
 * @date 05/12/2022
 */
#include <locale.h>     // setlocale
#include <ncurses.h>
#include <stdio.h>      // printf
#include <stdlib.h>     // srand
#include <time.h>       // time_t, time
#include "board.h"

/**
 * @brief Initial ncurses setup.
 */
static void init_setup() {
    setlocale(LC_ALL, "");      // enables Unicode support
    cbreak();                   // disable line buffering
    noecho();                   // user typed characters are not echoed
    keypad(stdscr, TRUE);       // support F1-F12 keys
    timeout(5);                 // non-blocking reading
    curs_set(0);                // hide cursor
}

int main() {
    int pause = 0;          // status variable; is iteration paused?
    int ch = 0;             // received user input
    int timer = 0;          // current timer's value
    int timer_limit = 50;   // after timer hits this value, make an iteration
    time_t t1;
    srand((unsigned)time(&t1));

    struct board_t b = { NULL, NULL };
    if (init_board(&b))
        goto err_board;

    initscr();
    init_setup();

    // print starting pos
    display_board(&b);

    do {
        ch = getch();
        switch (ch) {
            case KEY_UP:    // show what is above highest row
                if (pos_y + 1 <= 0)
                    pos_y++;
                break;
            case KEY_DOWN:  // show what is below lowest row
                if (pos_y - 1 + BOARD_HEIGHT >= LINES - 2)
                    pos_y--;
                break;
            case KEY_LEFT:  // show what is on the left
                if (pos_x + 1 <= 0)
                    pos_x++;
                break;
            case KEY_RIGHT: // show what is on the right
                if (pos_x - 1 + BOARD_WIDTH >= COLS - 2)
                    pos_x--;
                break;

            case '+':   // increase speed
                timer_limit = MAX(0, timer_limit-5);
                break;
            case '-':   // decrease speed
                timer_limit = MIN(100, timer_limit+5);
                break;

            case ' ':   // pause/resume iteration
                if (!pause)
                    timeout(-1);
                else
                    timeout(5);
                pause = !pause;
                break;
        }

        // allow to move screen when paused
        // no iteration is make when app is paused
        if (pause) {
            display_board(&b);
            continue;
        }

        if (timer < timer_limit) {
            timer++;
            continue;
        }

        // update board when timer limit is reached
        update_board(&b);
        display_board(&b);
        timer = 0;
        iteration++;
    } while (ch != 'q');

    endwin();
    destroy_board(&b);
    printf("Number of iteration: %d\n", iteration);
    return 0;
// handel when board could not be created.
err_board:
    return 1;
}

/* main.c */

