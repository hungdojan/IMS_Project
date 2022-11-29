#ifndef _BOARD_H_
#define _BOARD_H_

#include <ncurses.h>

#define BOARD_WIDTH   50
#define BOARD_HEIGHT  BOARD_WIDTH/2
#define CELL_ALIVE 'x'
#define CELL_DEAD  ' '
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

extern const char START_POS[BOARD_WIDTH * BOARD_HEIGHT + 1];

struct board_t {
    int w;
    int h;
    char *front;
    char *back;
};

int init_board(struct board_t *, int w, int h);
int update_board(struct board_t *b);
int display_board(struct board_t *b, WINDOW *win);
void destroy_board(struct board_t *b);

#endif // _BOARD_H_
