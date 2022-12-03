#include "board.h"
#include <stdlib.h>
#include <time.h>

static int nof_neighbors_row(struct board_t *b, int y, int x, enum state_t type)
{
    int count = 0;
    for (int i = MAX(0, x - 1); i <= MIN(x + 1, BOARD_WIDTH - 1); i++)
    {
        if (b->front[y * BOARD_WIDTH + i] == (char)type)
            count++;
    }
    return count;
}

static int nof_neighbors(struct board_t *b, int y, int x, enum state_t type)
{
    int count = 0;
    // upper row
    if (y > 0)
    {
        count += nof_neighbors_row(b, y - 1, x, type);
    }

    // middle row
    count += nof_neighbors_row(b, y, x, type);
    if (b->front[y * BOARD_WIDTH + x] == (char)type)
        count--;

    // lower row
    if (y < BOARD_HEIGHT - 1)
    {
        count += nof_neighbors_row(b, y + 1, x, type);
    }
    return count;
}

void apply_rules(struct board_t *b)
{
    // height
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        // column
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            int pos = i * BOARD_WIDTH + j;
            enum state_t value = b->front[pos];

            if (value == CELL_DEAD || (value >= CELL_AGE_START && value < CELL_AGE_START + b->nutrition_val))
            {

                // alive
                int alive_neighbors = nof_neighbors(b, i, j, CELL_ALIVE);
                switch (alive_neighbors)
                {
                case 1:
                    // OCCUPATION
                    b->back[pos] = (RAND(1000) < 125) ? CELL_ALIVE : b->front[pos];
                    if (b->back[pos] == CELL_ALIVE)
                    {
                        b->alive_counter++;
                        continue;
                    }

                    // NUTRIENT DEPLETION
                    if (RAND(1000) < 500)
                    {
                        if (b->front[pos] == CELL_DEAD)
                        {
                            b->back[pos] = CELL_AGE_START;
                        }
                        else if (b->front[pos] >= CELL_AGE_START)
                        {
                            b->back[pos] = b->front[pos] + 1;
                            if (b->back[pos] - CELL_AGE_START >= b->nutrition_val)
                            {
                                b->back[pos] = CELL_UNHABITED;
                                b->uninhabitable_counter++;
                            }
                        }
                    }
                    continue;
                case 2:
                    // OCCUPATION
                    if (b->nutrition_val > 3)
                    {
                        b->back[pos] = (RAND(1000) < 250) ? CELL_ALIVE : b->front[pos];
                        if (b->back[pos] == CELL_ALIVE)
                        {
                            b->alive_counter++;
                            continue;
                        }
                    }

                    // NUTRIENT DEPLETION
                    if (RAND(1000) < 750)
                    {
                        if (b->front[pos] == CELL_DEAD)
                        {
                            b->back[pos] = CELL_AGE_START;
                        }
                        else if (b->front[pos] >= CELL_AGE_START)
                        {
                            b->back[pos] = b->front[pos] + 1;
                            if (b->back[pos] - CELL_AGE_START >= b->nutrition_val)
                            {
                                b->back[pos] = CELL_UNHABITED;
                                b->uninhabitable_counter++;
                            }
                        }
                    }
                    continue;
                case 3:
                    // OCCUPATION
                    if (b->nutrition_val > 4)
                    {
                        b->back[pos] = (RAND(1000) < 500) ? CELL_ALIVE : b->front[pos];
                        if (b->back[pos] == CELL_ALIVE)
                        {
                            b->alive_counter++;
                            continue;
                        }
                    }

                    // NUTRIENT DEPLETION
                    if (b->front[pos] == CELL_DEAD)
                    {
                        b->back[pos] = CELL_AGE_START;
                    }
                    else if (b->front[pos] >= CELL_AGE_START)
                    {
                        b->back[pos] = b->front[pos] + 1;
                        if (b->back[pos] - CELL_AGE_START >= b->nutrition_val)
                        {
                            b->back[pos] = CELL_UNHABITED;
                            b->uninhabitable_counter++;
                        }
                    }
                    continue;
                case 4:
                    // OCCUPATION
                    if (b->nutrition_val > 5)
                    {
                        b->back[pos] = (RAND(1000) < 500) ? CELL_ALIVE : b->front[pos];
                        if (b->back[pos] == CELL_ALIVE)
                        {
                            b->alive_counter++;
                            continue;
                        }
                    }

                    // NUTRIENT DEPLETION
                    if (b->front[pos] == CELL_DEAD)
                    {
                        b->back[pos] = CELL_AGE_START;
                    }
                    else if (b->front[pos] >= CELL_AGE_START)
                    {
                        b->back[pos] = b->front[pos] + 1;
                        if (b->back[pos] - CELL_AGE_START >= b->nutrition_val)
                        {
                            b->back[pos] = CELL_UNHABITED;
                            b->uninhabitable_counter++;
                        }
                    }
                    continue;
                case 5:
                    // OCCUPATION
                    if (b->nutrition_val > 7)
                    {
                        b->back[pos] = (RAND(1000) < 500) ? CELL_ALIVE : b->front[pos];
                        if (b->back[pos] == CELL_ALIVE)
                        {
                            b->alive_counter++;
                            continue;
                        }
                    }

                    // NUTRIENT DEPLETION
                    if (b->front[pos] == CELL_DEAD)
                    {
                        b->back[pos] = CELL_AGE_START;
                    }
                    else if (b->front[pos] >= CELL_AGE_START)
                    {
                        b->back[pos] = b->front[pos] + 1;
                        if (b->back[pos] - CELL_AGE_START >= b->nutrition_val)
                        {
                            b->back[pos] = CELL_UNHABITED;
                            b->uninhabitable_counter++;
                        }
                    }
                    continue;
                case 6:
                case 7:
                case 8:
                    // NUTRIENT DEPLETION
                    if (b->front[pos] == CELL_DEAD)
                    {
                        b->back[pos] = CELL_AGE_START;
                    }
                    else if (b->front[pos] >= CELL_AGE_START)
                    {
                        b->back[pos] = b->front[pos] + 1;
                        if (b->back[pos] - CELL_AGE_START >= b->nutrition_val)
                        {
                            b->back[pos] = CELL_UNHABITED;
                            b->uninhabitable_counter++;
                        }
                    }
                    continue;
                }
            }
            else if (value == CELL_UNHABITED || value == CELL_ALIVE || value == CELL_CONIDIA || value == CELL_DIFF_MYCEL)
            {
                b->back[pos] = b->front[pos];
            }
        }
    }
}
