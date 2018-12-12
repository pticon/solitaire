#ifndef __GAME_H__
#define __GAME_H__

enum cell_state
{
	CELL_STATE_EMPTY,
	CELL_STATE_FILLED,
};

struct cell
{
	enum cell_state	state;
	struct cell	*up,
			*down,
			*left,
			*right;
};

#define  BOARD_X_MAX	7
#define  BOARD_Y_MAX	7

extern struct cell	board[BOARD_X_MAX][BOARD_Y_MAX];


void game_init(void);

int game_update(int x, int y);

void game_reset(void);

void game_destroy(void);


#endif /* __GAME_H__ */
