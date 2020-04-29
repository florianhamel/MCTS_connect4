NAME	=	connect4

PATH	=	./srcs/

SRCS	=	mcts.c tools.c checks.c main.c

_SRCS	=	$(addprefix $(PATH), $(SRCS))

OBJS	=	$(_SRCS:.c=.o)

DIR_H	=	includes

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

DEBUG	=	-g3 -fsanitize=address

all		:	$(NAME)

$(NAME)	:	$(OBJS)
			$(CC) $(OBJS) -o $(NAME)

debug	:	$(OBJS)
			$(CC) $(OBJS) -o $(NAME) $(DEBUG)

%.o		:	%.c
			$(CC) $(CFLAGS) -I$(DIR_H) -c $< -o $@

clean	:
			rm -f $(OBJS)

fclean	:	clean
			rm -f $(NAME)

re		:	fclean all
