#include "./includes/cub3d.h"


// char		*map[] = {
// 	"1111111111111111",
// 	"1000000000000001",
// 	"1000000100000001",
// 	"10000000P0000001",
// 	"1111111111111111",
// 	NULL};
// int			world_map[MAP_HEIGHT][MAP_WIDTH];

/* ---- Section 1: Utils, Map, FOV ---- */
void	cleanup(t_game *g)
{
	if (g->world_map)
	{
		free_int_map(g->world_map, g->map_info->map_height);
		g->world_map = NULL;
	}
    if (g->img)
        mlx_destroy_image(g->mlx, g->img);
    if (g->win)
    {
		mlx_destroy_window(g->mlx, g->win);
	}
	if(g->mlx)
	{	
		mlx_destroy_display(g->mlx);
		free(g->mlx);
	}
}


// void	fill_world_map(t_game *g)
// {
// 	int x, y;
// 	y = 0;
// 	while (y < MAP_HEIGHT)
// 	{
// 		x = 0;
// 		while (g->map_info->map_grid[y] && x < MAP_WIDTH)
// 		{
// 			if (g->map_info->map_grid[y][x] >= '1' && g->map_info->map_grid[y][x] <= '9')
// 				world_map[y][x] = g->map_info->map_grid[y][x] - '0';
// 			else
// 				world_map[y][x] = 0;
// 			x++;
// 		}
// 		y++;
// 	}
// }

void	set_fov_assist(t_game *g, char c)
{
	if (c == 'E')
	{
		g->dirX = 1;
		g->dirY = 0;
		g->planeX = 0;
		g->planeY = 0.66;
	}
	else if (c == 'W')
	{
		g->dirX = -1;
		g->dirY = 0;
		g->planeX = 0;
		g->planeY = -0.66;
	}
}

void	set_fov(t_game *g, char c)
{
	if (c == 'N')
	{
		g->dirX = 0;
		g->dirY = -1;
		g->planeX = 0.66;
		g->planeY = 0;
	}
	else if (c == 'S')
	{
		g->dirX = 0;
		g->dirY = 1;
		g->planeX = -0.66;
		g->planeY = 0;
	}
	else if (c == 'E' || c == 'W')
		set_fov_assist(g, c);
}

void	find_player_pos(t_game *g)
{
	g->posX = g->map_info->player_x;
	g->posY = g->map_info->player_y;

}

/* ---- Section 2: Texture Loading ---- */
int	load_texture_img(t_game *g, int idx, char *filename)
{
	int width;
	int height;
	int x;
	int y;
	int *tmp;
	g->tex_img[idx] = mlx_xpm_file_to_image(g->mlx, filename, &width, &height);
	if (!g->tex_img[idx])
		return (0);
	g->tex_data[idx] = mlx_get_data_addr(g->tex_img[idx], &g->tex_bpp[idx],
			&g->tex_size_line[idx], &g->tex_endian[idx]);
	y = 0;
	while (y < TEX_HEIGHT)
	{
		x = 0;
		while (x < TEX_WIDTH)
		{
			tmp = (int *)(g->tex_data[idx] + (y * g->tex_size_line[idx] + x
						* (g->tex_bpp[idx] / 8)));
			g->textures[idx][TEX_WIDTH * y + x] = *tmp;
			x++;
		}
		y++;
	}
	mlx_destroy_image(g->mlx, g->tex_img[idx]);
	return (1);
}

int	load_textures(t_game *g)
{
	int	i;

	char *files[NUM_TEXTURES] = {
		g->map_info->n_wall,
		g->map_info->e_wall,
		g->map_info->w_wall,
		g->map_info->s_wall
		};
	i = 0;
	while (i < NUM_TEXTURES)
	{
		if (!load_texture_img(g, i, files[i]))
			return (0);
		i++;
	}
	return (1);
}

/* ---- Section 3: Drawing/Pixels ---- */
void	put_pixel_to_image(t_game *g, int x, int y, int color)
{
	int	pixel;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pixel = (y * g->size_line) + (x * (g->bpp / 8));
		g->img_data[pixel + 0] = color & 0xFF;
		g->img_data[pixel + 1] = (color >> 8) & 0xFF;
		g->img_data[pixel + 2] = (color >> 16) & 0xFF;
	}
}

void	clear_image(t_game *g)
{
	int x, y;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel_to_image(g, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

void	draw_ceiling_and_floor(t_game *g, int x, int drawStart, int drawEnd)
{
	int	y;

	y = 0;
	while (y < drawStart)
		put_pixel_to_image(g, x, y++, g->map_info->ceiling_clr);
	y = drawEnd + 1;
	while (y < HEIGHT)
		put_pixel_to_image(g, x, y++, g->map_info->floor_clr);
}

/* ---- Section 4: Raycasting ---- */
void	init_ray_vars(t_game *g, int x, t_ray *r)
{
	r->cameraX = 2 * x / (double)WIDTH - 1;
	r->rayDirX = g->dirX + g->planeX * r->cameraX;
	r->rayDirY = g->dirY + g->planeY * r->cameraX;
	r->mapX = (int)g->posX;
	r->mapY = (int)g->posY;
	r->deltaDistX = (r->rayDirX == 0) ? 1e30 : fabs(1 / r->rayDirX);
	r->deltaDistY = (r->rayDirY == 0) ? 1e30 : fabs(1 / r->rayDirY);
}

void	init_dda(t_game *g, t_ray *r)
{
	if (r->rayDirX < 0)
	{
		r->stepX = -1;
		r->sideDistX = (g->posX - r->mapX) * r->deltaDistX;
	}
	else
	{
		r->stepX = 1;
		r->sideDistX = (r->mapX + 1.0 - g->posX) * r->deltaDistX;
	}
	if (r->rayDirY < 0)
	{
		r->stepY = -1;
		r->sideDistY = (g->posY - r->mapY) * r->deltaDistY;
	}
	else
	{
		r->stepY = 1;
		r->sideDistY = (r->mapY + 1.0 - g->posY) * r->deltaDistY;
	}
}

void	perform_dda(t_game *g, t_ray *r)
{
	r->hit = 0;
	while (!r->hit)
	{
		if (r->sideDistX < r->sideDistY)
		{
			r->sideDistX += r->deltaDistX;
			r->mapX += r->stepX;
			r->side = 0;
		}
		else
		{
			r->sideDistY += r->deltaDistY;
			r->mapY += r->stepY;
			r->side = 1;
		}
		if (r->mapX < 0 || r->mapX >= g->map_info->map_width ||
			r->mapY < 0 || r->mapY >= g->map_info->map_height
				|| g->world_map[r->mapY][r->mapX] > 0)
			r->hit = 1;
	}
}

void	calc_perp_wall_dist(t_ray *r, t_game *g)
{
	if (r->side == 0)
		r->perpWallDist = (r->mapX - g->posX + (1 - r->stepX) / 2) / r->rayDirX;
	else
		r->perpWallDist = (r->mapY - g->posY + (1 - r->stepY) / 2) / r->rayDirY;
	if (r->perpWallDist < 0.000001f)
		r->perpWallDist = 0.000001;
}

void	calc_draw_limits(t_ray *r)
{
	double	aspectRatio;
	
	aspectRatio = (double)WIDTH / HEIGHT;
	r->lineHeight = (int)((HEIGHT * 0.8) / r->perpWallDist * aspectRatio);
	// if(r->lineHeight < 0 || r->lineHeight > HEIGHT)
	// 	r->lineHeight = HEIGHT;
	r->drawStart = -r->lineHeight / 2 + HEIGHT / 2;
	if (r->drawStart < 0)
		r->drawStart = 0;
	r->drawEnd = r->lineHeight / 2 + HEIGHT / 2;
	if (r->drawEnd >= HEIGHT)
		r->drawEnd = HEIGHT - 1;
}

/* ---- Section 5: Raycasting Drawing ---- */
void	calc_wall_and_tex(t_ray *r, t_game *g)
{
	if (r->side == 0)
		r->wallX = g->posY + r->perpWallDist * r->rayDirY;
	else
		r->wallX = g->posX + r->perpWallDist * r->rayDirX;
	r->wallX -= floor(r->wallX);
	r->texX = (int)(r->wallX * (double)TEX_WIDTH);
	if ((r->side == 0 && r->rayDirX > 0) || (r->side == 1 && r->rayDirY < 0))
		r->texX = TEX_WIDTH - r->texX - 1;
}

void	draw_wall_and_floor(t_game *g, int x, t_ray *r)
{
	int texNum, y, texY, color;
	double step, texPos;
	if (r->side == 0)
		texNum = (r->stepX > 0) ? 3 : 2;
	else
		texNum = (r->stepY > 0) ? 1 : 0;
	step = 1.0 * TEX_HEIGHT / r->lineHeight;
	texPos = (r->drawStart - HEIGHT / 2 + r->lineHeight / 2) * step;
	y = r->drawStart;
	while (y < r->drawEnd)
	{
		texY = (int)texPos & (TEX_HEIGHT - 1);
		texPos += step;
		color = g->textures[texNum][TEX_HEIGHT * texY + r->texX];
		if (r->side == 1)
			color = (color >> 1) & 8355711;
		put_pixel_to_image(g, x, y, color);
		y++;
	}
	draw_ceiling_and_floor(g, x, r->drawStart, r->drawEnd);
}

void	cast_ray(t_game *g, int x)
{
	t_ray	r;

	init_ray_vars(g, x, &r);
	init_dda(g, &r);
	perform_dda(g, &r);
	calc_perp_wall_dist(&r, g);
	calc_draw_limits(&r);
	calc_wall_and_tex(&r, g);
	draw_wall_and_floor(g, x, &r);
}

void	render_frame(t_game *g)
{
	int	x;

	x = 0;
	clear_image(g);
	while (x < WIDTH)
	{
		cast_ray(g, x);
		x++;
	}
	mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
}

/* ---- Section 6: Movement/Rotation ---- */
double	ft_Check_collision(t_game *g, double newPosX, double newPosY)
{
	double	hitbox;

	hitbox = 0.02;
	if (g->world_map[(int)(newPosY + hitbox)][(int)(newPosX + hitbox)] > 0 ||
		g->world_map[(int)(newPosY - hitbox)][(int)(newPosX + hitbox)] > 0 ||
		g->world_map[(int)(newPosY + hitbox)][(int)(newPosX - hitbox)] > 0 ||
		g->world_map[(int)(newPosY - hitbox)][(int)(newPosX - hitbox)] > 0)
		return (0);
	return (1);
}

void	get_move_vector(int key, t_game *g, double *moveX, double *moveY)
{
	*moveX = 0;
	*moveY = 0;
	if (key == FORWARD_KEY)
		*moveX = g->dirX, *moveY = g->dirY;
	else if (key == BACKWARD_KEY)
		*moveX = -g->dirX, *moveY = -g->dirY;
	else if (key == LEFT_KEY)
		*moveX = -g->planeX, *moveY = -g->planeY;
	else if (key == RIGHT_KEY)
		*moveX = g->planeX, *moveY = g->planeY;
}

void	handle_movement(int key, t_game *g)
{
	double moveX, moveY, newPosX, newPosY;
	get_move_vector(key, g, &moveX, &moveY);
	if (moveX || moveY)
	{
		newPosX = g->posX + moveX * MOVE_SPEED;
		newPosY = g->posY + moveY * MOVE_SPEED;
		if (ft_Check_collision(g, newPosX, g->posY))
			g->posX = newPosX;
		if (ft_Check_collision(g, g->posX, newPosY))
			g->posY = newPosY;
	}
}

void	handle_rotation(int key, t_game *g)
{
	double oldDirX, oldPlaneX;
	if (key == LEFT_ARROW_KEY)
	{
		oldDirX = g->dirX;
		g->dirX = g->dirX * cos(-ROT_SPEED) - g->dirY * sin(-ROT_SPEED);
		g->dirY = oldDirX * sin(-ROT_SPEED) + g->dirY * cos(-ROT_SPEED);
		oldPlaneX = g->planeX;
		g->planeX = g->planeX * cos(-ROT_SPEED) - g->planeY * sin(-ROT_SPEED);
		g->planeY = oldPlaneX * sin(-ROT_SPEED) + g->planeY * cos(-ROT_SPEED);
	}
	else if (key == RIGHT_ARROW_KEY)
	{
		oldDirX = g->dirX;
		g->dirX = g->dirX * cos(ROT_SPEED) - g->dirY * sin(ROT_SPEED);
		g->dirY = oldDirX * sin(ROT_SPEED) + g->dirY * cos(ROT_SPEED);
		oldPlaneX = g->planeX;
		g->planeX = g->planeX * cos(ROT_SPEED) - g->planeY * sin(ROT_SPEED);
		g->planeY = oldPlaneX * sin(ROT_SPEED) + g->planeY * cos(ROT_SPEED);
	}
}

/* ---- Section 7: Hooks ---- */
int	handle_key(int key, t_game *g)
{
	if (key == ESC_KEY)
	{
		cleanup(g);
		exit(0);
	}
	handle_movement(key, g);
	handle_rotation(key, g);
	render_frame(g);
	return (0);
}

int	handle_exit(t_game *g)
{
	cleanup(g);
	exit(0);
	return (0);
}

int convert_char_map_to_int(t_game *g)
{
	int y;
	int	x;
	int k;

	y = 0;
    g->world_map = malloc(g->map_info->map_height * sizeof(int *));
    if (!g->world_map)
        return (1);

    while (y < g->map_info->map_height)
    {
        g->world_map[y] = malloc(g->map_info->map_width * sizeof(int));
        if (!g->world_map[y])
        {
            k = 0;
            while (k < y)
			{
            	free(g->world_map[k]);
				k++;
			}
			free(g->world_map);
            return (1);
        }
		x = 0;
        while (x < g->map_info->map_width)
        {
			if (g->map_info->map_grid[y][x] == '1')
				g->world_map[y][x] = 1;
            else
                g->world_map[y][x] = 0;
			x++;
        }
		y++;
    }
    return (0);
}
void free_int_map(int **int_map, int height)
{
	int y;

	y = 0;
    while (y < height)
	{
        free(int_map[y]);
		y++;
	}
	free(int_map);
}
/* ---- Section 8: main ---- */
int	big_bang(t_game g)
{

	g.mlx = mlx_init();
	if (!g.mlx)
		return (cleanup(&g), 1);
	g.win = mlx_new_window(g.mlx, WIDTH, HEIGHT, "Raycaster JiBooR");
	g.img = mlx_new_image(g.mlx, WIDTH, HEIGHT);
	g.img_data = mlx_get_data_addr(g.img, &g.bpp, &g.size_line, &g.endian);
	if (!g.win || !g.img || !g.img_data)
	{
		cleanup(&g);
		return (1);
	}
	set_fov(&g, g.map_info->player_dir);
	// fill_world_map(&g);
	if(convert_char_map_to_int(&g) == 1)
	{
		cleanup(&g);
		return (1);
	}
	// convert_char_map_to_int(&g);
	
	find_player_pos(&g);
	if (!load_textures(&g))
	{
		// free_int_map(g.world_map, g.map_info->map_height);
		cleanup(&g);
		print_error("Failed to load textures", g.map_info);
		return (1);
	}
	render_frame(&g);
	mlx_key_hook(g.win, handle_key, &g);
	mlx_hook(g.win, 17, 0, handle_exit, &g);
	mlx_loop(g.mlx);
	cleanup(&g);
	return (0);
}
