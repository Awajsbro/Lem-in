# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: awajsbro <awajsbro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/22 12:25:25 by awajsbro          #+#    #+#              #
#    Updated: 2018/10/16 15:58:43 by awajsbro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= lem-in

SRC_NAME		= main.c \
				check_anthill.c \
				room.c \
				pipe.c \
				path_finding.c \
				solve.c \
				solve2.c \
				delete_anthill.c \
				bonus.c \

SRC_PATH 		= ./src/

OBJ_PATH		= obj/
HEADER			= ./lem_in.h
CPP_FLAGS		= -Iinclude
LDFLAGS			= -Llibft
LDLIBS			= -lft
CC				= gcc
FLAGS			= -Wall -Wextra -Werror -g

OBJ_NAME		= $(SRC_NAME:.c=.o)
SRC				= $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ				= $(addprefix $(OBJ_PATH),$(OBJ_NAME))

all: $(NAME)

$(NAME): $(OBJ)
	@make all -C ./libft
	@$(CC) $(LDFLAGS) $(LDLIBS) $^ -o $@

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(HEADER)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(FLAGS) $(CPP_FLAGS) -o $@ -c $<

clean:
	@make clean -C ./libft
	@rm -fv $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

fclean: clean
	@make fclean -C ./libft
	@rm -fv $(NAME)

re: fclean all

.PHONY : clean fclean re all
