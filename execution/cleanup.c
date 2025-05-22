/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aourhou <aourhou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:48:42 by aourhou           #+#    #+#             */
/*   Updated: 2025/05/22 15:48:43 by aourhou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	cleanup(t_game *g)
{
	if (g->world_map)
	{
		free_int_map(g->world_map, g->map_info->map_height);
		g->world_map = NULL;
	}
	if (g->img)
	{
		mlx_destroy_image(g->mlx, g->img);
	}
	if (g->win)
	{
		mlx_destroy_window(g->mlx, g->win);
	}
	if (g->mlx)
	{
		mlx_destroy_display(g->mlx);
		free(g->mlx);
	}
	free_data(g->map_info);
}

void	set_fov_assist(t_game *g, char c)
{
	if (c == 'E')
	{
		g->dir_x = 1;
		g->dir_y = 0;
		g->plane_x = 0;
		g->plane_y = 0.66;
	}
	else if (c == 'W')
	{
		g->dir_x = -1;
		g->dir_y = 0;
		g->plane_x = 0;
		g->plane_y = -0.66;
	}
}

void	set_fov(t_game *g, char c)
{
	if (c == 'N')
	{
		g->dir_x = 0;
		g->dir_y = -1;
		g->plane_x = 0.66;
		g->plane_y = 0;
	}
	else if (c == 'S')
	{
		g->dir_x = 0;
		g->dir_y = 1;
		g->plane_x = -0.66;
		g->plane_y = 0;
	}
	else if (c == 'E' || c == 'W')
		set_fov_assist(g, c);
}

void	find_player_pos(t_game *g)
{
	g->pos_x = g->map_info->player_x;
	g->pos_y = g->map_info->player_y;
}
