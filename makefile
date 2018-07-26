# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: awajsbro <awajsbro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/22 12:25:25 by awajsbro          #+#    #+#              #
#    Updated: 2018/07/17 15:48:55 by awajsbro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= lem-in

MAIN		=	main.c \

MAIN_DEBUG	=	main_debug.c \

SRC			=	check_anthill.c \
				room.c \
				pipe.c \
				path_finding.c \
				solve.c \
				delete_anthill.c \
				bonus.c \

OBJ			=	$(SRC:.c=.o) $(MAIN:.c=.o)

OBJ_DEBUG	=	$(SRC:.c=.o) $(MAIN_DEBUG:.c=.o)

OBJDIR		=	obj/

SRCDIR		=	src/

LIB_DIR 	=	./libft/

LIBFT 		=	./libft/libft.a

FLAG		=	-Wall -Werror -Wextra -g

all :
	@$(MAKE) -C $(LIB_DIR)
	@mkdir -p $(OBJDIR)
	@gcc $(FLAG) -c $(addprefix $(SRCDIR), $(MAIN) $(SRC))
	@mv $(OBJ) $(OBJDIR)
	@gcc $(FLAG) $(addprefix $(OBJDIR), $(OBJ)) $(LIBFT) -o $(NAME)
	@echo "\033[36m	LEM-IN\033[33m    ====\033[1m> \033[32;1mREADY TO USE\033[0m"

nolib :
	@mkdir -p $(OBJDIR)
	@gcc $(FLAG) -c $(addprefix $(SRCDIR), $(MAIN) $(SRC))
	@mv $(OBJ) $(OBJDIR)
	@gcc $(FLAG) $(addprefix $(OBJDIR), $(OBJ)) $(LIBFT) -o $(NAME)
	@echo "\033[36m	LEM-IN\033[33m    ====\033[1m> \033[32;1mREADY TO USE\033[0m"

debug :
	@mkdir -p $(OBJDIR)
	@gcc -ggdb $(FLAG) -c $(addprefix $(SRCDIR), $(MAIN_DEBUG) $(SRC))
	@mv $(OBJ_DEBUG) $(OBJDIR)
	@gcc -ggdb $(FLAG) $(addprefix $(OBJDIR), $(OBJ_DEBUG)) $(LIBFT) -o $(NAME)
	@echo "\033[36m	LEM-IN\033[33m    ====\033[1m> \033[32;1mREADY TO USE\033[0m"

clean :
	@$(MAKE) clean -C $(LIB_DIR)
	@rm -rf $(OBJDIR)
	@echo "\033[31;1m	CLEANING DONE\033[0m"

fclean : clean
	@$(MAKE) fclean -C $(LIB_DIR)
	@rm $(NAME)
	@echo "\033[36m	LEM-IN\033[33m    ====\033[1m> \033[31;1mDELETED\033[0m"

re : fclean all
