/**
 * @brief Definition of functions that handles double buffering structure.
 *
 * This source code serves as submission for
 * a project of class IMS at FIT, BUT 2022/23.
 *
 * @file board.c
 * @authors Hung Do (xdohun00)
 *          Marek Dohnal (xdohna48)
 * @date 05/12/2022
 */
#include "board.h"
#include "board_setup.h"
#include <stdlib.h>     // calloc, free
#include <string.h>     // memmove

int pos_x = 0, pos_y = 0, iteration = 0;

int init_board(struct board_t *b) {
    if (b == NULL)
        return -1;
    b->back = calloc(BOARD_WIDTH * BOARD_HEIGHT, 1);
    if (b->back == NULL)    goto err_back;

    b->front = calloc(BOARD_WIDTH * BOARD_HEIGHT, 1);
    if (b->front == NULL)   goto err_front;

    // init starting grid with dots
    memmove(b->front, INIT_POS, BOARD_WIDTH * BOARD_HEIGHT);
    return 0;

err_front:
    free(b->back);
err_back:
    fprintf(stderr, "Not enough memory to initialize double buffering structure.\n");
    return 1;
}

static int nof_neighbors_row(struct board_t *b, int y, int x) {
    int count = 0;
    for (int i = MAX(0, x-1); i <= MIN(x+1, BOARD_WIDTH - 1); i++) {
        if (b->front[y * BOARD_WIDTH + i] == CELL_ALIVE)
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
    if (b->front[y * BOARD_WIDTH + x] == CELL_ALIVE)
        count--;

    // lower row
    if (y < BOARD_HEIGHT - 1) {
        count += nof_neighbors_row(b, y+1, x);
    }
    return count;
}

int update_board(struct board_t *b) {
    // height
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        // column
        for (int j = 0; j < BOARD_WIDTH; j++) {
            int neighbors = nof_neighbors(b, i, j);

            if (b->front[i * BOARD_WIDTH + j] == CELL_ALIVE) {
                // alive
                if (neighbors == 2 || neighbors == 3)
                    b->back[i * BOARD_WIDTH + j] = CELL_ALIVE;
                else
                    b->back[i * BOARD_WIDTH + j] = CELL_DEAD;
            } else {
                // dead
                if (neighbors == 3)
                    b->back[i * BOARD_WIDTH + j] = CELL_ALIVE;
                else
                    b->back[i * BOARD_WIDTH + j] = CELL_DEAD;
            }
        }
    }

    // buffer swap
    void *tmp = b->back;
    b->back = b->front;
    b->front = tmp;
    return 0;
}

int display_board(struct board_t *b) {
    // print chars one by one
    for (int i = 0; i < LINES && i-pos_y < BOARD_HEIGHT; i++) {
        for (int j = 0; j < COLS && j-pos_x < BOARD_WIDTH; j++) {
            mvprintw(i, j, "%c", b->front[(i-pos_y) * BOARD_WIDTH + (j-pos_x)]);
        }
    }
    refresh();
    return 0;
}

void destroy_board(struct board_t *b) {
    if (b == NULL)
        return;

    free(b->back);
    free(b->front);
}

/* board.c */
