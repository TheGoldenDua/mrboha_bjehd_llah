/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aourhou <aourhou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:49:08 by aourhou           #+#    #+#             */
/*   Updated: 2025/05/22 15:49:09 by aourhou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	load_texture_img(t_game *g, int idx, char *filename)
{
	int	width;
	int	height;
	int	x;
	int	y;
	int	*tmp;

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
	return (mlx_destroy_image(g->mlx, g->tex_img[idx]), 1);
}

int	load_textures(t_game *g)
{
	int		i;
	char	*files[NUM_TEXTURES];

	files[0] = g->map_info->n_wall;
	files[1] = g->map_info->e_wall;
	files[2] = g->map_info->w_wall;
	files[3] = g->map_info->s_wall;
	i = 0;
	while (i < NUM_TEXTURES)
	{
		if (!load_texture_img(g, i, files[i]))
			return (0);
		i++;
	}
	return (1);
}

void	calc_wall_and_tex(t_ray *r, t_game *g)
{
	if (r->side == 0)
		r->wall_x = g->pos_y + r->perpwalldist * r->raydir_y;
	else
		r->wall_x = g->pos_x + r->perpwalldist * r->raydir_x;
	r->wall_x -= floor(r->wall_x);
	r->tex_x = (int)(r->wall_x * (double)TEX_WIDTH);
	if ((r->side == 0 && r->raydir_x > 0) || (r->side == 1 && r->raydir_y < 0))
		r->tex_x = TEX_WIDTH - r->tex_x - 1;
}
