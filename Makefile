NAME = cub3D
SRC = main.c parsing/validate_map.c  parsing/map_utils.c  parsing/parse_utils0.c parsing/parse_utils1.c parsing/parse_utils2.c parsing/parse_utils3.c parsing/parse.c parsing/free.c parsing/parse_colors.c parsing/parse_map_info.c parsing/parse_textures.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c parsing/map_processing.c
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) -o $(NAME) $(SRC)

clean:
	rm -f $(NAME)
              