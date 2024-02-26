# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flo-dolc <flo-dolc@student.42roma.it>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/26 08:22:57 by flo-dolc          #+#    #+#              #
#    Updated: 2024/02/26 09:22:53 by flo-dolc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	$(shell find ./src -name "*.c")

OBJS		=	$(SRCS:.c=.o)

NAME		=	pipex

CC			=	gcc

CFLAGS		=	#-Wall -Wextra -Werror

RM			=	rm -f

INCLUDES	=	-Ilibft

LIBFT_FLAGS	=	-Llibft -lft

all:		$(NAME)

.c.o:
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) $(INCLUDES)

$(NAME):	$(OBJS)
			@make -C ./libft
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_FLAGS)

clean:
			$(RM) $(OBJS)
#@make -C ./libft clean

fclean:		clean
			$(RM) $(NAME)
#@make -C ./libft fclean

re:			fclean all

norm:
			@norminette $(shell find ./src -name "*.c")

.PHONY:		all clean fclean re norm
