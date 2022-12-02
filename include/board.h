/**
 * @brief Declaration of double buffer structure and its functions.
 *
 * This source code serves as submission for
 * a project of class IMS at FIT, BUT 2022/23.
 *
 * @file board.h
 * @authors Hung Do (xdohun00)
 *          Marek Dohnal (xdohna48)
 * @date 05/12/2022
 */
#ifndef _BOARD_H_
#define _BOARD_H_

#include <ncurses.h>

#define BOARD_WIDTH   100
#define BOARD_HEIGHT  100
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

enum state_t {
    CELL_DEAD=0,
    CELL_ALIVE,
    STATE_LEN
};

/** Starting coordinates of the board */
extern int pos_x;
extern int pos_y;

/** Number of iterations */
extern int iteration;

/**
 * @brief Implementation of double buffering.
 */
struct board_t {
    char *front;    /**< Newest buffer; to be displayed */
    char *back;     /**< Older buffer, to store updated board and swap with front */
};

/**
 * @brief Initialize double buffering structure.
 *
 * @param b Address of board structure.
 * @return Non-zero value when error occurs.
 */
int init_board(struct board_t *b);

/**
 * @brief Apply the rules to data.
 *
 * Output data will be stored into board_t::back buffer.
 * @param b Address of board structure.
 */
void apply_rules(struct board_t *b);

/**
 * @brief Calculate next iteration of the board.
 *
 * Rules are defined in this function. After finishing calculation function
 * swaps front and back buffers.
 * @param b Address of board structure.
 * @return Non-zero value when error occurs.
 */
int update_board(struct board_t *b);

/**
 * @brief Flush front buffer to STDOUT.
 *
 * @param b Address to board structure.
 * @return Non-zero value when error occurs.
 */
int display_board(struct board_t *b);

/**
 * @brief Structure memory clean up function.
 *
 * @param b Address to board structure.
 */
void destroy_board(struct board_t *b);

#endif // _BOARD_H_
