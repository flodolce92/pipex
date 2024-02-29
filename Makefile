# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flo-dolc <flo-dolc@student.42roma.it>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/26 08:22:57 by flo-dolc          #+#    #+#              #
#    Updated: 2024/02/29 05:32:54 by flo-dolc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_DIR	=	src/

SRC			=	pipex.c \
				execute.c \
				pipex_utils.c \
				ft_split.c

SRCS		=	$(addprefix $(SRCS_DIR), $(SRC))

OBJS_DIR	=	obj/

OBJS		=	$(addprefix $(OBJS_DIR), $(SRC:.c=.o))

NAME		=	pipex

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

RM			=	rm -f

INCLUDES	=	-Ilibft

LIBFT_FLAGS	=	-Llibft -lft

all:			$(NAME)

$(OBJS_DIR):
				mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o:	$(SRCS_DIR)%.c | $(OBJS_DIR)
				$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(NAME):		$(OBJS)
				@make -C ./libft
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_FLAGS)

clean:
				$(RM) $(OBJS)
#@make -C ./libft clean

fclean:			clean
				$(RM) $(NAME)
				$(RM) -r $(OBJS_DIR)
#@make -C ./libft fclean

re:				fclean all

norm:
				@norminette $(SRCS)

test:			re
				@clear
				@touch infile
				@rm -f $(OBJ)
				./pipex infile "ls -la" "grep .c" "wc -l" outfile
				@cat outfile
				@rm outfile
				< infile ls -la | grep .c | wc -l > outfile
				@cat outfile
				@rm outfile
				@echo ---------------------------------
				./pipex infile "echo 'il senzo della vita: 42\0'" "grep 42" "tr a-z A-Z" "head -10" "cat -e" "wc -l" outfile
				@cat outfile
				@rm outfile
				< infile echo 'il senzo della vita: 42\0' | grep 42 | tr a-z A-Z | head -10 | cat -e | wc -l > outfile
				@cat outfile
				@rm outfile
				@echo ---------------------------------
				@echo " a" > infile
				@echo " a" >> infile
				@echo " g" >> infile
				@echo " a" >> infile
				@echo "a" >> infile
				@echo "a" >> infile
				./pipex infile "grep ' '" "grep a" "head -10" "cat -e" "wc -l" outfile
				@cat outfile
				@rm outfile
				< infile grep ' ' | grep a | head -10 | cat -e | wc -l > outfile
				@cat outfile
				@echo ---------------------------------
				@rm infile
				@echo "===== CONTROLLO HERE_DOC ====="
				./pipex here_doc fine "grep '42'" "grep ' '" "cat -e" "wc" outfile
				@cat outfile
				grep 42 << fine | grep ' ' | cat -e | wc >> outfile
				@cat outfile
				@rm outfile
				@echo ---------------------------------
				@rm -f $(NAME)

.PHONY:			all clean fclean re norm test
