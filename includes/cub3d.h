#ifndef CUB3D_H
# define CUB3D_H

# include "../get_next_line/get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_map
{
	char	*n_wall;
	char	*s_wall;
	char	*w_wall;
	char	*e_wall;
	int		floor_clr;
	int		ceiling_clr;
	char	**map_grid;
	int		player_x;
	int		player_y;
	char	player_dir;
	int		map_height;
}			t_map;

//memory management and error handling
void		free_array(char ***arr);
void		free_wall(char **wall);
void		free_map_grid(char ***grid);
void		free_data(t_map *map);
void		free_textures(t_map *map);
void		free_lines(char **lines);
int			print_error(char *msg, t_map *map);

//Parsing textures and colors
int			handle_color_identifier(t_map *map, char **tokens);
int			set_color(int *color_field, char *value);
int			set_tex_path(char **texture, char *value);
int			handle_texture_identifier(t_map *map, char **tokens);
int			check_digit_and_range(char *str);
int			validate_rgb_values(char **color, int comma_count);
void		remove_new_line(char *line);
int			is_valid_identifier(t_map *map, char *token);
int			check_tex_extension(char *s);
int	parse_identifiers(char **file_content, t_map *map, int *i);

//Map parsing and validating
int			is_valid_char(char c);
int			get_max_width(char **map);
char		*fill_line_spaces(const char *line, int max_width);
int			check_row_walls(char *row);
int			check_side_walls(char *row);
int			check_space_surroundings(t_map *map);
int			get_map_height(char **lines, int start);
int			copy_real_map_lines(char **map_lines, int *index, t_map *map);
int			get_map_info(char **map_lines, int *index, t_map *map);
int			is_set(const char *s, char c);
int			is_map_line(char *line);
int			has_valid_border(char **map);
int			player_count_and_pos(char **map, t_map *data);
int			validate_map(t_map *map);
int	has_empty_lines_inside(char **map);

//parse functions
int			count_lines(int fd);
char		**read_all_lines(char *file, int fd);
int			is_line_empty(const char *line);
int			parse_cub_file(char *file, t_map *map);
void		init_data(t_map *map);
int			check_extension(char *s);

//libft utils
int			ft_atoi(const char *nptr);
char		*ft_strdup(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strtrim(char const *s1, char const *set);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
int			ft_isdigit(int c);
int			ft_count_word(char const *s, char c);
char		*ft_fill_word(char const *s, char c);
void		*free_split(char **str);
char		**ft_split(char const *s, char c);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memset(void *s, int c, size_t n);

#endif
