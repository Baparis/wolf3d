# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: baparis <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/27 23:33:38 by baparis           #+#    #+#              #
#    Updated: 2017/06/01 14:57:50 by baparis          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= wolf3d
FLAG= -Wall -Wextra -Werror
GRFLAG= -lmlx -framework OpenGL -framework Appkit
SRC= main.c\
	 parsing.c\
	 display.c\
	 detect.c \
	 init.c \
	 move.c \
	 scripts.c
OBJ = $(SRC:%c=%o)
LIB= libft/
LIBFT= libft/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIB)
	@gcc  $(LIBFT) -o $(NAME) -g $(SRC) $(GRFLAG)
	@echo "Compilation...  \xf0\x9f\x91\x8c"

%.o: %.c
	@gcc -o $@ -c $<

clean:
	@make clean -C $(LIB)
	@rm -rf $(OBJ)
	@echo "Fract'ol clean.\033[1;32mDONE \x1b[0m"

fclean: clean
	@rm -rf $(NAME)

re: fclean all
