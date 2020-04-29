 #include "../includes/connect4.h"

char	**malloc_board(void)
{
	char  **board;

	if (!(board = (char **)malloc(sizeof(char *) * 6)))
		return (NULL);
	for (int y = 0; y < 6; y++)
	{
		if (!(board[y] = (char *)malloc(sizeof(char) * 7)))
		{
			free_board(board);
			return (NULL);
		}
	}
	return (board);
}

void	init_board(char **board)
{
    for (int y = 0; y < 6; y++)
    	for (int x = 0; x < 7; x++)
        	board[y][x] = '.';
}

void	print_board(char **board)
{
	for (int y = 0; y < 6; y++)
	{
		for (int x = 0; x < 7; x++)
		printf("%c ", board[y][x]);
		printf("\n");
	}
	printf("\n");
}

int		get_last_move(t_node *node)
{
	for (int y = 5; y >= 0; y--)
		for (int x = 0; x < 7; x++)
      		if (node->board[y][x] != node->parent->board[y][x])
        		return (x);
  	return (-1);
}

char	get_skin(char **board, int lastMove)
{
	int	y;
	
	y = 0;
	while (y < 6)
	{
		if (board[y][lastMove] != '.')
			return (board[y][lastMove]);
		y++;
	}
	return (-1);
}

int		get_player(char **board, int lastMove) //the player that plays this turn
{
	char	skin;

	skin = get_skin(board, lastMove);
	if (skin == 'o')
		return (1);
	else
		return (0);
}

int		get_best_move(t_node *root)
{
	double	bestValue;
	int		bestMove;
	int		i;

	bestValue = -INFINITY;
	bestMove = 0;
	i = 0;
	while (i < root->nbChildren)
	{
		printf("--->child %d<---\n", i);
		printf("value: %.5f\n", root->children[i]->value);
		printf("nbExp: %d\n", root->children[i]->nbExp);
		printf("avrg val: %.5f\n",
		(double)(root->children[i]->value / root->children[i]->nbExp));
		if (root->children[i]->value / root->children[i]->nbExp > bestValue)
		{
			bestValue = root->children[i]->value / root->children[i]->nbExp;
			bestMove = i;
		}
		i++;
	}
	return (bestMove);
}

void	play_move(char **board, int move, int player)
{
	int y;

	y = 5;
	while (y >= 0 && board[y][move] != '.')
		y--;
	if (player)
		board[y][move] = 'x';
	else
		board[y][move] = 'o';
}

int		*get_avail_moves(char **board)
{
	int	*availMoves;
	int	i;

	if (!(availMoves = (int *)malloc(sizeof(int) * get_nb_children(board))))
		return (NULL);
	i = 0;
	for (int x = 0; x < 7; x++)
	{
		if (is_available(board, x))
		{
			availMoves[i] = x;
			i++;
		}
	}
	return (availMoves);
}

char	**board_dup(char **board)
{
	char  **newBoard;

	if (!(newBoard = (char **)malloc(sizeof(char *) * 6)))
		return (NULL);
	for (int y = 0; y < 6; y++)
	{
		if (!(newBoard[y] = (char *)malloc(sizeof(char) * 7)))
		{
			free_board(newBoard);
			return (NULL);
		}
	}
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 7; j++)
			newBoard[i][j] = board[i][j];
	return (newBoard);
}

void	free_board(char **board)
{
	for (int y = 0; y < 6; y++)
	{
		free(board[y]);
		board[y] = NULL;	
	}
	free(board);
	board = NULL;
}

void	free_tree(t_node *root)
{
	int	i;

	i = 0;
	while (i < root->nbChildren)
	{
		free_tree(root->children[i]);
		i++;
	}
	free_board(root->board);
	free(root);
}

int		get_nb_children(char **board)
{
    int nbChildren;

    nbChildren = 0;
    for (int x = 0; x < 7; x++)
    {
    	if (is_available(board, x))
    		nbChildren++;
    }
    return (nbChildren);
}

t_node	**make_children(t_node *node, int player)
{
	t_node  **children;
	int     j;

	if (!(children = (t_node **)malloc(sizeof(t_node *) * get_nb_children(node->board))))
		return (NULL);
	j = 0;
	for (int i = 0; i < 7; i++)
	{
		if (is_available(node->board, i))
		{
			children[j] = new_node(node, i, player);
			j++;
		}
  	}
	return (children);
}

t_node	*new_node(t_node *parent, int move, int player)
{
	t_node  *node;

	if (!(node = (t_node *)malloc(sizeof(t_node))))
	return (NULL);
	node->value = 0;
	node->nbExp = 0;
	node->parent = parent;
	node->nbChildren = 0;
	node->children = NULL;
	node->board = NULL;
	if (parent)
		node->board = board_dup(parent->board);
	if (move != -1 && player != -1)
		play_move(node->board, move, player); 
	return (node);
}
