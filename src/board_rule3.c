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

static int possible_to_grow(struct board_t *b, int y, int x) {
    // NW
    if (x-1 > 0 && y-1 > 0 &&
        b->front[y * BOARD_WIDTH + x] == CELL_UNOCCUPIED_NW)
        return 1;
    // N
    else if (y-1 > 0 &&
             b->front[y * BOARD_WIDTH + x] == CELL_UNOCCUPIED_N)
        return 1;
    // NE
    else if (x+1 < BOARD_WIDTH && y-1 > 0 &&
             b->front[y * BOARD_WIDTH + x] == CELL_UNOCCUPIED_NE)
        return 1;
    // W
    else if (x-1 > 0 &&
             b->front[y * BOARD_WIDTH + x] == CELL_UNOCCUPIED_W)
        return 1;
    // E
    else if (x+1 < BOARD_WIDTH &&
             b->front[y * BOARD_WIDTH + x] == CELL_UNOCCUPIED_E)
        return 1;
    // SW
    else if (x-1 > 0 && y+1 < BOARD_HEIGHT &&
             b->front[y * BOARD_WIDTH + x] == CELL_UNOCCUPIED_SW)
        return 1;
    // S
    else if (y+1 < BOARD_HEIGHT &&
             b->front[y * BOARD_WIDTH + x] == CELL_UNOCCUPIED_S)
        return 1;
    // SE
    else if (x+1 < BOARD_WIDTH && y+1 < BOARD_HEIGHT &&
             b->front[y * BOARD_WIDTH + x] == CELL_UNOCCUPIED_SE)
        return 1;
    return 0;

}

void apply_rules(struct board_t *b) {
    // height
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        // column
        for (int j = 0; j < BOARD_WIDTH; j++) {
            int pos = i * BOARD_WIDTH + j;

            if (b->front[pos] == CELL_DEAD) {
                b->back[pos] = CELL_UNOCCUPIED_N;
            } else if (b->front[pos] == CELL_UNOCCUPIED_N  || b->front[pos] == CELL_UNOCCUPIED_E  ||
                       b->front[pos] == CELL_UNOCCUPIED_W  || b->front[pos] == CELL_UNOCCUPIED_S  ||
                       b->front[pos] == CELL_UNOCCUPIED_NE || b->front[pos] == CELL_UNOCCUPIED_SE ||
                       b->front[pos] == CELL_UNOCCUPIED_NW || b->front[pos] == CELL_UNOCCUPIED_SW) {

                int r = rand() % 1000;
                // alive
                int alive_neighbors = nof_neighbors(b, i, j, CELL_ALIVE);
                switch(alive_neighbors) {
                    case 1:
                        if (r < 500) {
                            if (possible_to_grow(b, i, j))
                                b->back[pos] = CELL_ALIVE;
                            continue;
                        }
                    default:
                        b->back[pos] = b->front[pos] + 1;
                        if (b->back[pos] > CELL_UNOCCUPIED_SE)
                            b->back[pos] = CELL_UNOCCUPIED_N;
                        continue;
                }
            } else if (b->front[pos] == CELL_ALIVE) {
                b->back[pos] = b->front[pos];
            }
        }
    }
}
