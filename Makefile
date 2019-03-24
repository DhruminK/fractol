# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkhatri <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/18 15:10:07 by dkhatri           #+#    #+#              #
#    Updated: 2019/03/22 17:44:12 by dkhatri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

MAIN = main.c

FLAGS = -Wall -Wextra -Werror

SRCDIR = ./src/

HELPER = ft_comp.c ft_init.c ft_iterations.c ft_mlx_func.c ft_color_conv.c \
		ft_thread_func.c ft_hook_func.c ft_pt.c ft_key_hook.c

PARSOR = 

SRCO = $(addprefix $(SRCDIR), $(PARSOR:.c=.o)) \
		$(addprefix $(SRCDIR), $(HELPER:.c=.o)) \
		$(MAIN:.c=.o)

DEPS = ./includes/fractol.h ./libft/libft.h

%.o: %.c $(DEPS)
	gcc $(FLAGS) -o $@ -c $<

all: $(NAME)

$(NAME): $(SRCO)
	make -C libft
	gcc -o $(NAME) $(SRCO) -L libft/ -lft -L /usr/local/lib -lmlx \
		-framework OpenGL -framework AppKit

clean :
	make -C libft clean
	/bin/rm -f $(SRCO)

fclean : clean
	make -C libft fclean
	/bin/rm -f $(NAME)

re : fclean all

.PHONY : clean fclean all re
