#ifndef CONNECT4_H
# define CONNECT4_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>

typedef	struct	s_node
{
  double		value;
  int			nbExp;
  struct s_node	*parent;
  int			nbChildren;
  struct s_node	**children;
  char	**board;
}				t_node;

// mcts.c
double	UCB1(t_node *root, t_node *node); //test needed
t_node	*selection(t_node *root, t_node *node); //test needed
int		simulation(char **board, int lastmove);
void	expand(t_node *node, int player); //test needed
void	back_propagation(); //test needed
int		mcts(t_node *root, int iter);

// tools.c
char	**malloc_board(void);
void	init_board(char **board);
void	print_board(char **board);
int		get_last_move(t_node *node);
char	get_skin(char **board, int lastMove);
int		get_player(char **board, int lastMove);
int		get_best_move(t_node *root); //test needed
void	play_move(char **board, int move, int player);
int		get_nb_avail_moves(char **board);
int		*get_avail_moves(char **board);
void	free_tree(t_node *root);
char	**board_dup(char **board);
void	free_board(char **board);
int		get_nb_children(char **board);
t_node	**make_children(t_node *node, int player);
t_node	*new_node(t_node *parent, int move, int player);

// checks.c
int		game_over(char **board, int lastMove);
int		win(char **board, int lastMove);
int		diag_low(char **board, int lastMove);
int		diag_high(char **board, int lastMove);
int		col(char **board, int lastMove);
int		row(char **board, int lastMove);
int		is_available(char **board, int col);
int		nb_moves(char **board);
int		draw(char **board); //test needed

#endif