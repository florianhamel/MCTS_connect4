#include "../includes/connect4.h"
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
	/*char  board[6][7] =	{{'.', '.', '.', '.', '.', '.', '.'},
						 {'x', '.', '.', '.', '.', '.', '.'},
						 {'o', 'x', '.', '.', '.', '.', 'x'},
						 {'o', 'x', 'x', '.', 'o', 'x', 'x'},
						 {'x', 'x', 'o', 'x', 'x', 'o', 'o'},
						 {'o', 'o', 'x', 'x', 'o', 'x', 'o'}};
	
	printf("diag_low: %d\n", diag_low(board, atoi(av[1])));
	printf("diag_high: %d\n", diag_high(board, atoi(av[1])));
	printf("win: %d\n", win(board, atoi(av[1])));*/
	
	/*char	**board = malloc_board();
	init_board(board);
	t_node	*newNode = new_node(NULL, -1, -1);
	print_board(newNode->board);
	t_node	*node = new_node(newNode, 3, 1);
	print_board(node->board);
	printf("nb_children: %d\n", get_nb_children(node));
	printf("get_last_move: %d\n", get_last_move(node));
	printf("get_skin: %c\n", get_skin(node, get_last_move(node)));
	free_board(node->board);
	printf("%s\n", node->board[0]);*/
	
	//TEST: make_children, free_tree, simulation
	/*t_node	*root;

	root = new_node(NULL, -1, -1);
	root->board = malloc_board();
	init_board(root->board);
	root->nbChildren = get_nb_children(root->board);
	root->children = make_children(root, 1);
	int i = 0;
	while (i < root->nbChildren)
	{
		print_board(root->children[i]->board);	
		i++;
		printf("\n");
	}
	printf("%d\n", simulation(board_dup(root->board), -1));
	free_tree(root);

	//TEST: get_avail_moves
	char	**board = malloc_board();
	init_board(board);
	int i = 0;
	int	*availMoves = get_avail_moves(board);
	printf("nbChildren: %d\n", get_nb_children(board));
	while (i < get_nb_children(board))
	{
		printf("availMoves[%d]: %d\n", i, availMoves[i]);
		i++;
	}*/
	return (0);
}
