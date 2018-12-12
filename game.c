#include "game.h"


struct cell	board[BOARD_X_MAX][BOARD_Y_MAX];

static int	last_x = -1,
		last_y = -1;


void game_init(void)
{
	int	i,
		j;

	for ( j = 0 ; j < BOARD_Y_MAX ; j++ )
	{
		for ( i = 0 ; i < BOARD_X_MAX ; i++ )
		{
			if ( i == 3 && j == 3 )
				board[i][j].state = CELL_STATE_EMPTY;
			else
				board[i][j].state = CELL_STATE_FILLED;
		}
	}
}

static int game_get_distance(int a, int b)
{
	if ( a > b )
		return a - b;

	return b - a;
}

static int game_is_valid_move(int from_x, int from_y, int to_x, int to_y, struct cell **between)
{
	int	dist;

	if ( from_x == to_x && from_y == to_y )
		return 0;

	if ( board[from_x][from_y].state != CELL_STATE_FILLED ||
		board[to_x][to_y].state != CELL_STATE_EMPTY )
		return 0;

	if ( from_x == to_x )
	{
		if ( (dist = game_get_distance(from_y, to_y)) != 2 )
			return 0;

		if ( from_y > to_y )
			*between = &board[from_x][from_y-1];
		else
			*between = &board[from_x][to_y-1];

		return 1;
	}
	else if ( from_y == to_y )
	{
		if ( (dist = game_get_distance(from_x, to_x)) != 2 )
			return 0;

		if ( from_x > to_x )
			*between = &board[from_x-1][from_y];
		else
			*between = &board[to_x-1][from_y];

		return 1;
	}

	return 0;
}

static void game_move(int from_x, int from_y, int to_x, int to_y, struct cell *between)
{
	board[from_x][from_y].state = CELL_STATE_EMPTY;
	board[to_x][to_y].state = CELL_STATE_FILLED;

	between->state = CELL_STATE_EMPTY;
}

int game_update(int x, int y)
{
	struct cell	*between;

	if ( last_x == -1 && last_y == -1 )
	{
		last_x = x;
		last_y = y;

		return 0;
	}

	if ( game_is_valid_move(last_x, last_y, x, y, &between) )
		game_move(last_x, last_y, x, y, between);

	last_x = last_y = -1;

	return 1;
}

void game_reset(void)
{
	last_x = last_y = -1;

	game_init();
}

void game_destroy(void)
{
}
