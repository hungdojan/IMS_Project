#include "board.h"
#include <stdlib.h>
#include <time.h>

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

void apply_rules(struct board_t *b) {
    // height
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        // column
        for (int j = 0; j < BOARD_WIDTH; j++) {
            int neighbors = nof_neighbors(b, i, j);

            if (b->front[i * BOARD_WIDTH + j] == CELL_DEAD) {

                // time_t t1;
                // srand((unsigned)time(&t1));
                int r = rand() % 1000;
                // alive
                switch(neighbors) {
                    case 1:
                        b->back[i * BOARD_WIDTH + j] = (r < 125) ? CELL_ALIVE : CELL_DEAD;
                        break;
                    case 2:
                        b->back[i * BOARD_WIDTH + j] = (r < 250) ? CELL_ALIVE : CELL_DEAD;
                        break;
                    case 3:
                        b->back[i * BOARD_WIDTH + j] = (r < 500) ? CELL_ALIVE : CELL_DEAD;
                        break;
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                        b->back[i * BOARD_WIDTH + j] = CELL_DEAD;
                        break;
                }
                // if (neighbors == 2 || neighbors == 3)
                //     b->back[i * BOARD_WIDTH + j] = CELL_ALIVE;
                // else
                //     b->back[i * BOARD_WIDTH + j] = CELL_DEAD;
            } else if (b->front[i * BOARD_WIDTH + j] == CELL_ALIVE) {
                b->back[i * BOARD_WIDTH + j] = CELL_ALIVE;
            }
            // } else {
            //     // dead
            //     if (neighbors == 3)
            //         b->back[i * BOARD_WIDTH + j] = CELL_ALIVE;
            //     else
            //         b->back[i * BOARD_WIDTH + j] = CELL_DEAD;
            // }
    }
}
}
