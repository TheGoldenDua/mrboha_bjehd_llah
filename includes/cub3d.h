/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aourhou <aourhou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:32:05 by del-ganb          #+#    #+#             */
/*   Updated: 2025/05/22 15:43:57 by aourhou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../get_next_line/get_next_line.h"
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 2048
# define HEIGHT 1080
# define MOVE_SPEED 0.5
# define ROT_SPEED 0.05
# define MAP_WIDTH 16
# define MAP_HEIGHT 5
# define NUM_TEXTURES 4
# define TEX_HEIGHT 32
# define TEX_WIDTH 32
# define ESC_KEY 65307
# define FORWARD_KEY 65362
# define BACKWARD_KEY 65364
# define LEFT_KEY 65361
# define RIGHT_KEY 65363
# define LEFT_ARROW_KEY 97
# define RIGHT_ARROW_KEY 100

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
	int		map_width;
}			t_map;

typedef struct s_draw_wall_vars
{
	int		tex_num;
	int		y;
	int		tex_y;
	int		color;
	double	step;
	double	tex_pos;
}			t_draw_wall_vars;

typedef struct s_ray
{
	double	raydir_x;
	double	camera_x;
	double	raydir_y;
	double	deltadist_x;
	double	deltadist_y;
	double	sidedist_x;
	double	sidedist_y;
	double	perpwalldist;
	double	wall_x;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	int		hit;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_x;
}			t_ray;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	int		bpp;
	int		size_line;
	int		endian;
	void	*img;
	char	*img_data;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		textures[NUM_TEXTURES][TEX_WIDTH * TEX_HEIGHT];
	void	*tex_img[NUM_TEXTURES];
	char	*tex_data[NUM_TEXTURES];
	int		tex_bpp[NUM_TEXTURES];
	int		tex_size_line[NUM_TEXTURES];
	int		tex_endian[NUM_TEXTURES];
	t_map	*map_info;
	int		**world_map;
}			t_game;

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
int			parse_identifiers(char **file_content, t_map *map, int *i);

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
int			has_empty_lines_inside(char **map);
int			read_lines_into_array(char **lines, int fd, int size);
char		**alloc_lines_array(int size);
int			is_invalid_tokens(char **tokens);
int			validate_map(t_map *map);

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

//execution functions
void		calc_wall_and_tex(t_ray *r, t_game *g);
int			load_textures(t_game *g);
int			load_texture_img(t_game *g, int idx, char *filename);
void		calc_draw_limits(t_ray *r);
void		calc_perp_wall_dist(t_ray *r, t_game *g);
void		perform_dda(t_game *g, t_ray *r);
void		init_dda(t_game *g, t_ray *r);
void		init_ray_vars(t_game *g, int x, t_ray *r);
void		render_frame(t_game *g);
void		cast_ray(t_game *g, int x);
void		draw_wall_and_floor(t_game *g, int x, t_ray *r);
int			calc_step_y(int y);
int			calc_step_x(int x);
double		ft_check_collision(t_game *g, double new_pos_x, double new_pos_y);
void		get_move_vector(int key, t_game *g, double *move_x, double *move_y);
void		handle_movement(int key, t_game *g);
void		handle_rotation(int key, t_game *g);
int			handle_key(int key, t_game *g);
int			handle_exit(t_game *g);
void		purge(t_game *g, int y);
int			convert_char_map_to_int(t_game *g);
void		free_int_map(int **int_map, int height);
void		put_pixel_to_image(t_game *g, int x, int y, int color);
void		clear_image(t_game *g);
void		draw_ceiling_and_floor(t_game *g, int x, int draw_start,
				int draw_end);
void		cleanup(t_game *g);
void		set_fov_assist(t_game *g, char c);
void		set_fov(t_game *g, char c);
void		find_player_pos(t_game *g);
int			big_bang(t_game g);

#endif
