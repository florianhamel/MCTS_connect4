#include "connect4.h"

// 'x' -> 1 and 'o' -> 0

void game(void)
{
	char    **board;
	t_node  *root;
	int     humanMove;
	int     aiMove;

	board = malloc_board();
	init_board(board);
	aiMove = -1;
	while (!game_over(board, aiMove))
	{
		printf("Move from 0 to 6:\n");
		scanf("%d", &humanMove);
		play_move(board, humanMove, 0);
		print_board(board);
		if (!game_over(board, humanMove))
		{
			root = new_node(NULL, -1, -1);
			root->board = board_dup(board);
			expand(root, 1);
			aiMove = mcts(root, 20);
			play_move(board, aiMove, 1);
			print_board(board);
			free_tree(root);
		}
		else
			break ;
	}
}

int main(void)
{
	game();
	return (0);
}
