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

#define BOARD_WIDTH   400
#define BOARD_HEIGHT  200
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define RAND(limit) (rand() % limit)
#define MIN(a,b) ((a) < (b) ? (a) : (b))

#define DEFINE_COLOR(name_val, r, g, b) \
    do {\
        init_color(name_val, \
                   (int)(r / 255.0 * 1000), \
                   (int)(g / 255.0 * 1000), \
                   (int)(b / 255.0 * 1000));\
    } while (0)

/**
 * @brief List of custom colors.
 */
enum custom_color_t {
    CC_LIGHT_GRAY=30,
    CC_ALMOST_BLACK,
    CC_LIGHT_RED,
};

/**
 * @brief List of cell states.
 */
enum state_t {
    // model 1
    CELL_DEAD=0,
    CELL_ALIVE,
    // model 2
    CELL_UNHABITED,
    // model 3
    CELL_UNOCCUPIED_N,
    CELL_UNOCCUPIED_SW,
    CELL_UNOCCUPIED_E,
    CELL_UNOCCUPIED_NW,
    CELL_UNOCCUPIED_S,
    CELL_UNOCCUPIED_NE,
    CELL_UNOCCUPIED_W,
    CELL_UNOCCUPIED_SE,
    CELL_DIFF_MYCEL,
    CELL_CONIDIA,
    STATE_LEN,
    // dynamic model 2
    CELL_AGE_START=50,
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
    int max_iter;       /**< Maximal number of iterations; -1 means no limit */
    int nutrition_val;  /**< Number of steps before cell becomes unhabited (defaults 1) */
    int alive_counter;  /**< Number of cells that are alive */
    char *front;        /**< Newest buffer; to be displayed */
    char *back;         /**< Older buffer, to store updated board and swap with front */
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
