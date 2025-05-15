
#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <stdlib.h> //exit()
#include <fcntl.h> //open()
#include <stdio.h> //close()
#include "../get_next_line/get_next_line.h"

typedef struct s_map
{
    char *N_wall;
    char *S_wall;
    char *W_wall;
    char *E_wall;
    int Floor_clr;
    int Ceiling_clr;
    char **map_grid; 
    int player_x;
    int player_y;
    char player_dir;
}t_map;


//memory management and error handling
void	free_array(char ***arr);
void	free_wall(char **wall);
void	free_map_grid(char ***grid);
void	free_data(t_map *map);
void free_lines(char **lines);
void free_textures(t_map *map);
int print_error(char *msg, t_map *map);
void	init_data(t_map *map);

//parser functions
int	check_extension(char *s);
int	parse_cub_file(char *file, t_map *map);
int	parse_identifiers(char **file_content, t_map *map, int *i);
char **read_all_lines(char *file, int fd);

//Parsing textures and colors
int set_tex_path(char **texture, char *value);
int parse_tex(char *line, t_map *map);
int	set_ceiling_color(t_map *map, char **color);
int	set_floor_color(t_map *map, char **color);
// int	set_color(char *line, t_map *map);
int set_color(int *color_field, char *value);
int is_valid_identifier(t_map *map, char **token);
int validate_color_format(char *line);
int	check_digit_and_range(char *str);
int	validate_rgb_values(char **color, int comma_count);

//Map parsing and validating
int	is_valid_char(char c);
int	is_surrounded(char **map, int x, int y);
int	get_max_width(char **map);
void	fill_line_spaces(char *line, int max_width);
void	normalize_map(t_map *map);
int	check_row_walls(char *row);
int	check_side_walls(char *row);
int	is_out_of_bounds(char **map, int x, int y);
int	is_valid_neighbor(char c);
int	check_space_surroundings(char **map);
int	count_real_map_lines(char **map_lines);
int	copy_real_map_lines(char **map_lines, t_map *map, int max_width);
int	get_map_info(char **map_lines, t_map *map);
int	validate_rgb_values(char **color, int comma_count);
int	check_digit_and_range(char *str);
int validate_color_format(char *line);
int	check_all_identifiers(t_map *map);
int	is_map_line(char *line);
int is_empty_line(char *line);
int	validate_map(t_map *map);
int	check_map_shape_padding(char **map);
int check_enclosure(char **map);
int	is_map_whitespace_only(char **map);
int	check_minimum_elements(char **map);
int	player_count_and_pos(char **map, t_map *data);
int	has_valid_border(char **map);
int	is_file_content_empty(char **lines);

//libft utils
int	ft_atoi(const char *nptr);
char	*ft_strdup(const char *s);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strtrim(char const *s1, char const *set);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int	ft_isdigit(int c);
int	ft_count_word(char const *s, char c);
char	*ft_fill_word(char const *s, char c);
void	*free_split(char **str);
char	**ft_split(char const *s, char c);
int	is_set(const char *s, char c);

#endif

