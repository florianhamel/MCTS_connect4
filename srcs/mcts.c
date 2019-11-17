#include "connect4.h"

double	UCB1(t_node *root, t_node *node)
{
	double	av_val;
	double	exp_val;

	if (node->nbExp == 0)
		return (+INFINITY);
	av_val = (node->value / node->nbExp); //average value
	exp_val = 100 * sqrt(log(root->nbExp) / node->nbExp); //exploration value
	return (av_val + exp_val);
}

t_node	*selection(t_node *root, t_node *node)
{
	t_node	*bestChild;
	double	tmpValue;
	double	bestValue;
	int		i;

	if (node->children == NULL) //basic case
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

int		mcts(t_node *root, int iter) //return the column that seems most interesting
{
	t_node  *bestNode;
	int     bestMove;
	int     ret;

	if (!iter)
	{
		bestMove = get_best_move(root);
		return (bestMove);
	}
	bestNode = selection(root, root); //SELECTION
	if (win(bestNode->board, get_last_move(bestNode))) //PROVEN WIN/LOSS
	{
		if (get_skin(bestNode->board, get_last_move(bestNode)) == 'o')
			bestNode->parent->value = -INFINITY;
		ret = simulation(board_dup(bestNode->board), get_last_move(bestNode));
		back_propagation(bestNode, ret);
		//check article: INFINITY values 
	}
	else if (bestNode->nbExp == 0) //NOT EXPLORED YET
	{
		ret = simulation(board_dup(bestNode->board), get_last_move(bestNode));
		back_propagation(bestNode, ret);
	}
	else
	{
		expand(bestNode, get_player(bestNode->board, get_last_move(bestNode)));
		ret = simulation(board_dup(bestNode->board), get_last_move(bestNode));
		back_propagation(bestNode, ret);
	}
	return (mcts(root, iter - 1));
}
