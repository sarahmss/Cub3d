# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/11 17:02:33 by smodesto          #+#    #+#              #
#    Updated: 2022/07/28 00:06:23 by smodesto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D
LIBFT	= ./libraries/libft/libft.a
MLX		= ./libraries/minilibx-linux/libmlx.a

LIBFT_PATH		= ./libraries/libft/
MLX_PATH		= ./libraries/minilibx-linux/
SRC_PATH		= ./source/
INCLUDES_PATH	= ./includes/
OBJS_PATH		= ./objects/

SRCS_FILES =	init/main.c				\
				init/init.c				\
				init/leave.c			\
				parsing/file_handling.c	\
				parsing/get_elements.c	\
				parsing/map_parsing.c	\
				parsing/check_map.c		\
				mlx/events.c			\
				mlx/img.c				\
				game/draw.c				\
				game/ft_rgbhex.c		\
				game/controls.c			\
				game/minimap.c			\
				game/2D_to_3D.c			\
				game/textures.c			\
				game/textures_utils.c	\
				raycasting/aux_cast.c	\
				raycasting/get_scene.c	\
				raycasting/math.c		\
				raycasting/raycasting.c	\
				raycasting/set_point.c



SRCS = $(addprefix $(SRC_PATH), $(SRCS_FILES))

OBJS_FILES	= $(patsubst %.c, %.o, $(SRCS_FILES))
OBJS = $(addprefix $(OBJS_PATH), $(OBJS_FILES))

HEADER_FILES	=	cub3d.h			\
					keymap.h		\
					my_mlx_draw.h	\
					raycasting.h

HEADERS = $(addprefix $(INCLUDES_PATH), $(HEADER_FILES))

CC			= gcc
FLAGS		= -Wall -Wextra -g
LIBRARIES	= -L$(LIBFT_PATH) -L$(MLX_PATH) -lmlx -lXext -lX11 -lft -lm
INCLUDES	= -I$(INCLUDES_PATH) -I$(LIBFT_PATH) -I$(MLX_PATH)

all:		$(NAME)

$(NAME):	$(OBJS) $(LIBFT) $(MLX)
			$(CC) $(OBJS) $(FLAGS) $(LIBRARIES) $(INCLUDES)  -o $(NAME)

$(OBJS_PATH)%.o : $(SRC_PATH)%.c $(HEADERS)
			@mkdir -p objects
			@mkdir -p objects/init
			@mkdir -p objects/parsing
			@mkdir -p objects/mlx
			@mkdir -p objects/raycasting
			@mkdir -p objects/game

			$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
$(MLX):
			@echo making minilibx...
			@echo --------------------------
			@make -sC $(MLX_PATH)
			@echo --------------------------
			@echo done!

$(LIBFT):
			@echo making libft...
			@echo --------------------------
			@make -sC $(LIBFT_PATH)
			@echo done!
			@echo --------------------------

clean:
			@make -sC $(LIBFT_PATH) fclean
			@make -sC $(LIBFT_PATH) clean
			@rm -f $(OBJS)
			echo cleaned!

fclean:		clean
			@rm -f $(NAME)
			@rm -rf objects
			@rm -rf objects/raycasting
			@rm -rf objects/init
			@rm -rf objects/parsing
			@rm -rf objects/mlx

re: fclean all

.PHONY: all clean fclean re
