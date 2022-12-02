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
#include <stdlib.h>     // calloc, free, srand, rand
#include <string.h>     // memmove
#include <time.h>       // time

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

int update_board(struct board_t *b) {
    apply_rules(b);

    // buffer swap
    void *tmp = b->back;
    b->back = b->front;
    b->front = tmp;
    return 0;
}

int display_board(struct board_t *b) {
    static char printable_chars[] = {
        ' ',    // CELL_DEAD
        'o'     // CELL_ALIVE
    };

    // print chars one by one
    for (int i = 0; i < LINES && i-pos_y < BOARD_HEIGHT; i++) {
        for (int j = 0; j < COLS && j-pos_x < BOARD_WIDTH; j++) {
            int pos = (i-pos_y) * BOARD_WIDTH + (j-pos_x);
            enum state_t value = b->front[pos];

            mvprintw(i, j, "%c", printable_chars[value]);
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
