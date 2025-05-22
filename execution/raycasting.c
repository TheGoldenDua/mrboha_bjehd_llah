/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aourhou <aourhou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:49:03 by aourhou           #+#    #+#             */
/*   Updated: 2025/05/22 15:49:04 by aourhou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_ray_vars(t_game *g, int x, t_ray *r)
{
	r->camera_x = 2 * x / (double)WIDTH - 1;
	r->raydir_x = g->dir_x + g->plane_x * r->camera_x;
	r->raydir_y = g->dir_y + g->plane_y * r->camera_x;
	r->map_x = (int)g->pos_x;
	r->map_y = (int)g->pos_y;
	if (r->raydir_x == 0)
		r->deltadist_x = 1e30;
	else
		r->deltadist_x = fabs(1 / r->raydir_x);
	if (r->raydir_y == 0)
		r->deltadist_y = 1e30;
	else
		r->deltadist_y = fabs(1 / r->raydir_y);
}

void	init_dda(t_game *g, t_ray *r)
{
	if (r->raydir_x < 0)
	{
		r->step_x = -1;
		r->sidedist_x = (g->pos_x - r->map_x) * r->deltadist_x;
	}
	else
	{
		r->step_x = 1;
		r->sidedist_x = (r->map_x + 1.0 - g->pos_x) * r->deltadist_x;
	}
	if (r->raydir_y < 0)
	{
		r->step_y = -1;
		r->sidedist_y = (g->pos_y - r->map_y) * r->deltadist_y;
	}
	else
	{
		r->step_y = 1;
		r->sidedist_y = (r->map_y + 1.0 - g->pos_y) * r->deltadist_y;
	}
}

void	perform_dda(t_game *g, t_ray *r)
{
	r->hit = 0;
	while (!r->hit)
	{
		if (r->sidedist_x < r->sidedist_y)
		{
			r->sidedist_x += r->deltadist_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->sidedist_y += r->deltadist_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (r->map_x < 0 || r->map_x >= g->map_info->map_width || r->map_y < 0
			|| r->map_y >= g->map_info->map_height
			|| g->world_map[r->map_y][r->map_x] > 0)
			r->hit = 1;
	}
}

void	calc_perp_wall_dist(t_ray *r, t_game *g)
{
	if (r->side == 0)
	{
		r->perpwalldist = (r->map_x - g->pos_x + (1 - r->step_x) / 2)
			/ r->raydir_x;
	}
	else
	{
		r->perpwalldist = (r->map_y - g->pos_y + (1 - r->step_y) / 2)
			/ r->raydir_y;
	}
	if (r->perpwalldist < 0.000001f)
		r->perpwalldist = 0.000001;
}

void	calc_draw_limits(t_ray *r)
{
	double	aspect_ratio;

	aspect_ratio = (double)WIDTH / HEIGHT;
	r->line_height = (int)((HEIGHT * 0.8) / r->perpwalldist * aspect_ratio);
	r->draw_start = -r->line_height / 2 + HEIGHT / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_height / 2 + HEIGHT / 2;
	if (r->draw_end >= HEIGHT)
		r->draw_end = HEIGHT - 1;
}
