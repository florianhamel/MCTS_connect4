#include "connect4.h"

double	UCB1(t_node *root, t_node *node)
{
	double	av_val;
	double	expl_val;
	double	const_expl;
	
	if (node->nbExp == 0)
		return (+INFINITY);
	const_expl = 125; // exploration constant is empirically determined
	av_val = (node->value / node->nbExp);
	expl_val = const_expl * sqrt(log(root->nbExp) / node->nbExp);
	return (av_val + expl_val);
}

t_node	*selection(t_node *root, t_node *node)
{
	t_node	*bestChild;
	double	tmpValue;
	double	bestValue;
	int		i;

	if (node->children == NULL)
		return (node);
	bestChild = node->children[0];
	bestValue = -INFINITY;
	i = 0;
	while (i < node->nbChildren)
	{	
		tmpValue = UCB1(root, node->children[i]);
		if (tmpValue > bestValue)
		{
			bestValue = tmpValue;
			bestChild = node->children[i];
		}
		i++;
	}
	return (selection(root, bestChild));
}

int		simulation(char **board, int lastMove)
{
	int				*availMoves;
	int				randMove;
	struct timeval	*start;
	
	if (lastMove != -1 && win(board, lastMove))
	{
		if (get_skin(board, lastMove) == 'x')
			return (43 - nb_moves(board));
		else
			return (nb_moves(board) - 43);
	}
	else if (draw(board))
		return (0);
	availMoves = get_avail_moves(board);
	if (!(start = (struct timeval *)malloc(sizeof(struct timeval))))
		return (0);
	gettimeofday(start, NULL);
	randMove = availMoves[start->tv_usec % get_nb_children(board)];
	if (lastMove == -1)
		play_move(board, randMove, 1);
	else
		play_move(board, randMove, get_player(board, lastMove));
	free(availMoves);
	free(start);
	return (simulation(board, randMove));
}

void	expand(t_node *node, int player)
{
	node->nbChildren = get_nb_children(node->board);
	node->children = make_children(node, player);
}

void	back_propagation(t_node *node, int ret)
{
	while (node != NULL)
	{
		node->value += ret;
		node->nbExp += 1;
		node = node->parent;
	}
}

int		mcts(t_node *root, int iter) // return the best move
{
	t_node  *bestNode;
	char	**board_cpy;
	int     bestMove;
	int     ret;

	if (!iter)
	{
		bestMove = get_best_move(root);
		return (bestMove);
	}
	bestNode = selection(root, root);
	board_cpy = board_dup(bestNode->board);
	if (win(bestNode->board, get_last_move(bestNode))) // proven win/loss
	{
		if (get_skin(bestNode->board, get_last_move(bestNode)) == 'o')
			bestNode->parent->value = -INFINITY;
		ret = simulation(board_cpy, get_last_move(bestNode));
		back_propagation(bestNode, ret);
	}
	else if (bestNode->nbExp == 0) // not explored yet
	{
		ret = simulation(board_cpy, get_last_move(bestNode));
		back_propagation(bestNode, ret);
	}
	else // expand the node and simulate from its first child
	{
		expand(bestNode, get_player(bestNode->board, get_last_move(bestNode)));
		board_cpy = board_dup(bestNode->children[0]->board);
		ret = simulation(board_cpy, get_last_move(bestNode->children[0]));
		back_propagation(bestNode, ret);
	}
	free(board_cpy);
	return (mcts(root, iter - 1));
}
