#include "../includes/connect4.h"

int diag_high(char **board, int lastMove)
{
	char  skin;
	int   x;
	int   y;
	int   count;

	skin = get_skin(board, lastMove);
	x = lastMove;
	y = 0;
	while (board[y][lastMove] == '.')
		y++;
	while (x > 0 && y < 5)
	{
		x--;
		y++;
	}
	count = 0;
	while (x < 7 && y >= 0)
	{
		if (board[y][x] == skin)
			count++;
		else
			count = 0;
		if (count == 4)
			return (1);
		x++;
		y--;
	}
	return (0);
}

int diag_low(char **board, int lastMove)
{
  	int   x;
	int   y;
	char  skin;
	int   count;

	skin = get_skin(board, lastMove);
	x = lastMove;
	y = 0;
	while (board[y][lastMove] == '.')
		y++;
	while (x > 0 && y > 0)
	{
		x--;
		y--;
	}
	count = 0;
	while (x < 7 && y < 6)
	{
		count = (board[y][x] == skin) ? count + 1 : 0;
		if (count == 4)
			return (1);
		x++;
		y++;
	}
	return (0);
}

int col(char **board, int lastMove)
{
    char  skin;
    int   count;
    int   y;

    y = 0;
    while (y < 6 && board[y][lastMove] == '.')
      y++;
    skin = board[y][lastMove];
    count = 0;
    while (y < 6 && board[y][lastMove] == skin)
    {
      y++;
      count++;
    }
    if (count >= 4)
      return (1);
    return (0);
}

int row(char **board, int lastMove)
{
	char  skin;
	int   count;
	int   y;
	int   x;

	y = 0;
	while (y < 6 && board[y][lastMove] == '.')
		y++;
	skin = board[y][lastMove];
	count = 0;
	x = 0;
	while (x < 7)
	{
		if (board[y][x] == skin)
			count += 1;
		else
			count = 0;
		if (count == 4)
			return (1);
		x++;
	}
	return (0);
}

int win(char **board, int lastMove)
{
	if (diag_low(board, lastMove) || diag_high(board, lastMove))
		return (1);
	if (col(board, lastMove) || row(board, lastMove))
		return (1);
	return (0);
}

int	draw(char **board)
{
	for (int x = 0; x < 7; x++)
	{
		if (is_available(board, x))
			return (0);
	}
	return (1);
}

int	game_over(char **board, int lastMove)
{
	if (lastMove == -1)
		return (0);
	if (win(board, lastMove) || draw(board))
		return (1);
	return (0);
}

int is_empty(char **board)
{
	for (int y = 0; y < 6; y++)
	{
		for (int x = 0; x < 7; x++)
		{
			if (board[y][x] != '.')
				return (0);
		}
	}
	return (1);
}

int is_available(char **board, int col)
{
  	return (board[0][col] == '.');
}

int	nb_moves(char **board)
{
	int	nbMoves;

	nbMoves = 0;
	for (int y = 0; y < 6; y++)
	{	
		for(int x = 0; x < 7; x++)
		{
			if (board[y][x] != '.')
				nbMoves++;
		}
	}
	return (nbMoves);
}
