/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_drawing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aourhou <aourhou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:48:59 by aourhou           #+#    #+#             */
/*   Updated: 2025/05/22 15:49:00 by aourhou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	calc_step_x(int x)
{
	if (x > 0)
		return (3);
	else
		return (2);
}

int	calc_step_y(int y)
{
	if (y > 0)
		return (1);
	else
		return (0);
}

void	draw_wall_and_floor(t_game *g, int x, t_ray *r)
{
	t_draw_wall_vars	v;

	if (r->side == 0)
		v.tex_num = calc_step_x(r->side);
	else
		v.tex_num = calc_step_y(r->step_y);
	v.step = 1.0 * TEX_HEIGHT / r->line_height;
	v.tex_pos = (r->draw_start - HEIGHT / 2 + r->line_height / 2) * v.step;
	v.y = r->draw_start;
	while (v.y < r->draw_end)
	{
		v.tex_y = (int)v.tex_pos & (TEX_HEIGHT - 1);
		v.tex_pos += v.step;
		v.color = g->textures[v.tex_num][TEX_HEIGHT * v.tex_y + r->tex_x];
		if (r->side == 1)
			v.color = (v.color >> 1) & 8355711;
		put_pixel_to_image(g, x, v.y, v.color);
		v.y++;
	}
	draw_ceiling_and_floor(g, x, r->draw_start, r->draw_end);
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
