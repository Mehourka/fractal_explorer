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

# Colors
GREEN	=	\033[0;32m
RED		=	\033[0;31m
BLUE	=	\033[0;34m
NC		=	\033[0m


# Tester : git@github.com:LeoFu9487/push_swap_tester.git

NAME	=	fractol
LIBDIR	=	lib/
INCDIR	=	include/
SRCDIR	=	src/
BONDIR	=	bonus/

LIBFT	=	$(LIBDIR)/libft
LIBMLX	=	$(LIBDIR)/MLX42

INCLUDES=	-I $(LIBDIR)/libft -I $(INCDIR) -I $(LIBMLX)/include
LIBS	=	$(LIBFT)/libft.a $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm -L"/Users/$(USER)/.brew/opt/glfw/lib/"

# Compiler and flags
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra
CFLAGS +=	-Wunreachable-code -Ofast
RM		=	rm

# Sources

SRCS	=	main.c				\
			ft_map.c			\
			mlx_mandelbrot.c	\
			mlx_keyboard_hooks.c\
			mlx_mouse_hooks.c	\
			mlx_vectors.c		\
			mlx_init.c			\
			mlx_julia.c			\
			mlx_utils.c			\
			mlx_render.c			\

BONUS	= 	bonus_main.c				\


# Objects
OBJDIR	=	obj/
OBJS		:=	$(SRCS:%.c=$(OBJDIR)%.o)
SRCS		:=	$(SRCS:%.c=$(SRCDIR)%.c)
BONUS		:=	$(BONUS:%=$(BONDIR)%)
DEPS		:=	$(OBJS:%.o=%.d)


#------------------------------------------------------------------------------#
#                                TARGETS                                       #
#------------------------------------------------------------------------------#

all : libmlx libft $(NAME) execute

execute : $(NAME)
	./$(NAME) $(ARGS)

# Compile program
$(NAME) : $(OBJS)
	@echo "$(GREEN)	Compiling $(NAME)... $(NC)"
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME) -I. $(INCLUDES)

# Compile libft
libft:
	@ $(MAKE) -C $(LIBFT) -s

#Compiling libmlx
libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4 -s

# Compile objects
$(OBJDIR)%.o : $(SRCDIR)%.c
	@mkdir -p $(OBJDIR);
	@$(CC) -c $(CFLAGS) -MMD -MP $< -o $@ $(INCLUDES)

# Compile Bonus
$(OBJDIR)%.o : $(BONDIR)%.c
	@mkdir -p $(OBJDIR);
	@$(CC) -c $(CFLAGS) -MMD -MP $< -o $@

-include $(DEPS)

# Remove objects
clean :
	@$(RM) -rf $(OBJDIR)
	@rm -rf $(LIBMLX)/build
	@echo "$(RED)	Removed objects	$(NC)"

# Remove all
fclean : clean
	@$(RM) -f $(NAME) $(BONUS)
	@$(RM) -rf $(NAME).dSYM

	@$(MAKE) fclean -C $(LIBFT) -s
	@echo "$(RED)	Removed executables and libft	$(NC)"

# Remake
re : fclean all

leak :
	echo "$(BLUE)	Checking leaks ...	$(NC)"
	valgrind --leak-check=full --show-leak-kinds=all --trace-children=no --track-fds=no ./$(NAME) $(ARGS)

.PHONY:
	clean fclean re test all directories visualizer leak libft libmlx