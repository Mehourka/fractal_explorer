# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/29 12:50:46 by kmehour           #+#    #+#              #
#    Updated: 2023/06/05 11:22:17 by kmehour          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#------------------------------------------------------------------------------#
#                                VARIABLES                                     #
#------------------------------------------------------------------------------#


# Tester : git@github.com:LeoFu9487/push_swap_tester.git

NAME	=	fractol
LDIR	=	lib/
IDIR	=	include/

LIBFT	=	$(LDIR)/libft
LIBMLX	=	$(LDIR)/MLX42

INCLUDES=	-I $(LDIR)/libft -I $(IDIR) -I $(LIBMLX)/include
LIBS	=	$(LIBFT)/libft.a $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm -L"/Users/$(USER)/.brew/opt/glfw/lib/"


# Colors
GREEN	=	\033[0;32m
RED		=	\033[0;31m
BLUE	=	\033[0;34m
NC		=	\033[0m

# Compiler and flags
CC		=	gcc
# CFLAGS	=	-Wall -Werror -Wextra
CFLAGS +=	-Wunreachable-code -Ofast
RM		=	rm

# Sources
SDIR	=	src/
BDIR	=	bonus/

SRCS	=	main.c				\
			ft_map.c			\
			mlx_mandelbrot.c	\
			mlx_nav_hooks.c		\
			mlx_vectors.c		\
			tests.c				\


# Objects
ODIR	=	obj/
OBJS		:=	$(SRCS:%.c=$(ODIR)%.o)

SRCS		:=	$(SRCS:%.c=$(SDIR)%.c)


#------------------------------------------------------------------------------#
#                                TARGETS                                       #
#------------------------------------------------------------------------------#

all : libmlx libft $(NAME) exec

exec : $(NAME)
	./$(NAME) $(ARGS)

# Compile exec
$(NAME) : $(OBJS)
	@echo "$(GREEN)	Compiling $(NAME)... $(NC)"
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME) -I. $(INCLUDES)

# Compile libft
libft:
# @echo "$(BLUE)	Compiling libft ...	$(NC)"m
	@ $(MAKE) -C $(LIBFT) -s

#Compiling libmlx
libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4 -s

# Compile objects
$(ODIR)%.o : $(SDIR)%.c
	@mkdir -p $(ODIR);
	@$(CC) -c $(CFLAGS) $< -o $@ $(INCLUDES)

# Compile Bonus
$(ODIR)%.o : $(BDIR)%.c
	@mkdir -p $(ODIR);
	@$(CC) -c $(CFLAGS) $< -o $@

# Remove objects
clean :
	@$(RM) -rf $(ODIR)
	@rm -rf $(LIBMLX)/build
	@echo "$(RED)	Removed objects	$(NC)"

# Remove all
fclean : clean
	@$(RM) -f $(NAME) $(BONUS)
	@$(RM) -rf $(NAME).dSYM

	@$(MAKE) fclean -C $(LIBFT) -s
	@echo "$(RED)	Removed executablesand libft	$(NC)"

# Remake
re : fclean all

leak :
	echo "$(BLUE)	Checking leaks ...	$(NC)"
	valgrind --leak-check=full --show-leak-kinds=all --trace-children=no --track-fds=no ./$(NAME) $(ARGS)

test:
	@echo $(dir $(LIBFT))

visualizer:
	./push_swap_visualizer/build/bin/visualizer

.PHONY:
	clean fclean re test all directories visualizer leak libft libmlx