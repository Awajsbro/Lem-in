# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: awajsbro <awajsbro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/22 12:25:25 by awajsbro          #+#    #+#              #
#    Updated: 2018/10/19 10:54:27 by awajsbro         ###   ########.fr        #
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

HEADER			= ./lem_in.h

SRC_PATH 		= src/
OBJ_PATH		= obj/

CPP_FLAGS		= -Iinclude
LDFLAGS			= -Llibft
LDLIBS			= -lft

CC				= gcc
FLAGS			= -Wall -Wextra -Werror

OBJ_NAME		= $(SRC_NAME:.c=.o)

SRC				= $(addprefix $(SRC_PATH),$(SRC_NAME) $(SRC_MAIN))
OBJ				= $(addprefix $(OBJ_PATH),$(OBJ_NAME) $(OBJ_MAIN))

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
