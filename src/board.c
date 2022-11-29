#include "board.h"
#include <stdlib.h>
#include <string.h>

const char START_POS[] =
//          01234567890123456789012345678901234567890123456789
/* 0 */    "                                                  "
/* 1 */    "                                                  "
/* 2 */    "                                                  "
/* 3 */    "      x                                           "
/* 4 */    "       xx                                         "
/* 5 */    "      xx                                          "
/* 6 */    "                                                  "
/* 7 */    "                                                  "
/* 8 */    "                                                  "
/* 9 */    "                                                  "
/* 0 */    "                                                  "
/* 1 */    "                                                  "
/* 2 */    "                                                  "
/* 3 */    "                                                  "
/* 4 */    "                                                  "
/* 5 */    "                    xxx                           "
/* 6 */    "                                                  "
/* 7 */    "                   x                              "
/* 8 */    "                  x                               "
/* 9 */    "                                                  "
/* 0 */    "                                                  "
/* 1 */    "                                                  "
/* 2 */    "                                                  "
/* 3 */    "                                                  "
/* 4 */    "                                                  ";


// here write your code
int init_board(struct board_t *b, int w, int h) {
    if (b == NULL)
        return -1;
    b->back = calloc(w*h+1, 1);
    if (b->back == NULL)    goto err_back;

    b->front = calloc(w*h, 1);
    if (b->front == NULL)   goto err_front;

    b->w = w;
    b->h = h;

    // init starting grid with dots
    memmove(b->front, START_POS, w*h+1);
    return 0;

err_front:
    free(b->back);
err_back:
    return 1;
}

static int nof_neighbors_row(struct board_t *b, int y, int x) {
    int count = 0;
    for (int i = MAX(0, x-1); i <= MIN(x+1, b->w - 1); i++) {
        if (b->front[y * b->w + i] == CELL_ALIVE)
            count++;
    }
    return count;
}

static int nof_neighbors(struct board_t *b, int y, int x) {
    int count = 0;
    // upper row
    if (y > 0) {
        count += nof_neighbors_row(b, y-1, x);
    }

    // middle row
    count += nof_neighbors_row(b, y, x);
    if (b->front[y * b->w + x] == CELL_ALIVE)
        count--;

    // lower row
    if (y < b->h - 1) {
        count += nof_neighbors_row(b, y+1, x);
    }
    return count;
}

int update_board(struct board_t *b) {
    // height
    for (int i = 0; i < b->h; i++) {
        // column
        for (int j = 0; j < b->w; j++) {
            int neighbors = nof_neighbors(b, i, j);
            // printw("y: %d, x: %d, n: %d\n", i, j, neighbors);

            if (b->front[i * b->w + j] == CELL_ALIVE) {
                // alive
                if (neighbors == 2 || neighbors == 3)
                    b->back[i * b->w + j] = CELL_ALIVE;
                else
                    b->back[i * b->w + j] = CELL_DEAD;
            } else {
                // dead
                if (neighbors == 3)
                    b->back[i * b->w + j] = CELL_ALIVE;
                else
                    b->back[i * b->w + j] = CELL_DEAD;
            }
        }
    }

    void *tmp = b->back;
    b->back = b->front;
    b->front = tmp;
    return 0;
}

int display_board(struct board_t *b, WINDOW *win) {
    mvwprintw(win, 0, 0, "%s", b->front);
    // box(win, 0, 0);
    wrefresh(win);
    return 0;
}

void destroy_board(struct board_t *b) {
    if (b == NULL)
        return;

    free(b->back);
    free(b->front);
}

/* board.c */
