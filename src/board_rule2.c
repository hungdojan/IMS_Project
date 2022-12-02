#include "board.h"
#include <stdlib.h>
#include <time.h>

static int nof_neighbors_row(struct board_t *b, int y, int x, enum state_t type) {
    int count = 0;
    for (int i = MAX(0, x-1); i <= MIN(x+1, BOARD_WIDTH - 1); i++) {
        if (b->front[y * BOARD_WIDTH + i] == (char)type)
            count++;
    }
    return count;
}

static int nof_neighbors(struct board_t *b, int y, int x, enum state_t type) {
    int count = 0;
    // upper row
    if (y > 0) {
        count += nof_neighbors_row(b, y-1, x, type);
    }

    // middle row
    count += nof_neighbors_row(b, y, x, type);
    if (b->front[y * BOARD_WIDTH + x] == (char)type)
        count--;

    // lower row
    if (y < BOARD_HEIGHT - 1) {
        count += nof_neighbors_row(b, y+1, x, type);
    }
    return count;
}

void apply_rules(struct board_t *b) {
    // height
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        // column
        for (int j = 0; j < BOARD_WIDTH; j++) {
            int pos = i * BOARD_WIDTH + j;
            enum state_t value = b->front[pos];

            if (value == CELL_DEAD || value == CELL_AGE1
                || value == CELL_AGE2 || value == CELL_AGE3) {

                int r = rand() % 1000;
                // alive
                int alive_neighbors = nof_neighbors(b, i, j, CELL_ALIVE);
                switch(alive_neighbors) {
                    case 1:
                        b->back[pos] = (r < 125) ? CELL_ALIVE : b->front[pos];
                        if (b->back[pos] == CELL_ALIVE)
                            continue;
                        if (b->front[pos] == CELL_DEAD) {
                            b->back[pos] = (r < 500) ? CELL_AGE1 : CELL_DEAD;
                        } else {
                            b->back[pos] = (r < 500) ? b->front[pos] + 1 : b->front[pos];
                        }
                        continue;
                    case 2:
                        if (b->front[pos] == CELL_DEAD) {
                            b->back[pos] = (r < 750) ? CELL_AGE1 : CELL_DEAD;
                        } else {
                            b->back[pos] = (r < 750) ? b->front[pos] + 1 : b->front[pos];
                        }
                        continue;
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                        if (b->front[pos] == CELL_DEAD) {
                            b->back[pos] = CELL_AGE1;
                        } else {
                            b->back[pos]++;
                        }
                        continue;
                }
            } else if (b->front[pos] == CELL_ALIVE) {
                b->back[pos] = b->front[pos];
            } else if (b->front[pos] == CELL_UNHABITED) {
                b->back[pos] = b->front[pos];
            }
        }
    }
}
