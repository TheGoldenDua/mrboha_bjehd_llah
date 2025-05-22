/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_rotation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aourhou <aourhou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:48:55 by aourhou           #+#    #+#             */
/*   Updated: 2025/05/22 15:48:56 by aourhou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double	ft_check_collision(t_game *g, double new_pos_x, double new_pos_y)
{
	double	hitbox;
	double	x;
	double	y;
	double	xx;

	hitbox = 0.02;
	x = new_pos_x + hitbox;
	y = new_pos_y + hitbox;
	xx = new_pos_x - hitbox;
	if (g->world_map[(int)(y)][(int)(x)] > 0 ||
		g->world_map[(int)(new_pos_y - hitbox)][(int)(x)] > 0 ||
		g->world_map[(int)(y)][(int)(xx)] > 0 ||
		g->world_map[(int)(new_pos_y - hitbox)][(int)(xx)] > 0)
		return (0);
	return (1);
}

void	get_move_vector(int key, t_game *g, double *move_x, double *move_y)
{
	*move_x = 0;
	*move_y = 0;
	if (key == FORWARD_KEY)
	{
		*move_x = g->dir_x;
		*move_y = g->dir_y;
	}
	else if (key == BACKWARD_KEY)
	{
		*move_x = -g->dir_x;
		*move_y = -g->dir_y;
	}
	else if (key == LEFT_KEY)
	{
		*move_x = -g->plane_x;
		*move_y = -g->plane_y;
	}
	else if (key == RIGHT_KEY)
	{
		*move_x = g->plane_x;
		*move_y = g->plane_y;
	}
}

void	handle_movement(int key, t_game *g)
{
	double	move_x;
	double	move_y;
	double	new_pos_x;
	double	new_pos_y;

	get_move_vector(key, g, &move_x, &move_y);
	if (move_x || move_y)
	{
		new_pos_x = g->pos_x + move_x * MOVE_SPEED;
		new_pos_y = g->pos_y + move_y * MOVE_SPEED;
		if (ft_check_collision(g, new_pos_x, g->pos_y))
			g->pos_x = new_pos_x;
		if (ft_check_collision(g, g->pos_x, new_pos_y))
			g->pos_y = new_pos_y;
	}
}

void	handle_rotation(int key, t_game *g)
{
	double	old_dir_x;
	double	old_plane_x;

	if (key == LEFT_ARROW_KEY)
	{
		old_dir_x = g->dir_x;
		g->dir_x = g->dir_x * cos(-ROT_SPEED) - g->dir_y * sin(-ROT_SPEED);
		g->dir_y = old_dir_x * sin(-ROT_SPEED) + g->dir_y * cos(-ROT_SPEED);
		old_plane_x = g->plane_x;
		g->plane_x = g->plane_x * cos(-ROT_SPEED) - g->plane_y
			* sin(-ROT_SPEED);
		g->plane_y = old_plane_x * sin(-ROT_SPEED) + g->plane_y
			* cos(-ROT_SPEED);
	}
	else if (key == RIGHT_ARROW_KEY)
	{
		old_dir_x = g->dir_x;
		g->dir_x = g->dir_x * cos(ROT_SPEED) - g->dir_y * sin(ROT_SPEED);
		g->dir_y = old_dir_x * sin(ROT_SPEED) + g->dir_y * cos(ROT_SPEED);
		old_plane_x = g->plane_x;
		g->plane_x = g->plane_x * cos(ROT_SPEED) - g->plane_y * sin(ROT_SPEED);
		g->plane_y = old_plane_x * sin(ROT_SPEED) + g->plane_y * cos(ROT_SPEED);
	}
}
