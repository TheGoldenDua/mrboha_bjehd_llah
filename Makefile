NAME = cub3D
SRC = main.c parsing/validate_map.c  parsing/map_utils.c  parsing/parse_utils0.c parsing/parse_utils1.c parsing/parse_utils2.c parsing/parse_utils3.c parsing/parse.c parsing/free.c parsing/parse_colors.c parsing/parse_map_info.c parsing/parse_textures.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c parsing/map_processing.c
SRC += execution/big_bang.c execution/cleanup.c execution/draw_pixels.c execution/hooks.c execution/movement_rotation.c execution/raycasting_drawing.c execution/raycasting.c execution/textures.c
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

all: $(NAME)

MLX = -lmlx -lX11 -lXext -lm
$(NAME): $(SRC)
	$(CC) $(CFLAGS) -o $(NAME) $(SRC) $(MLX)

clean:
	rm -f $(NAME)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
