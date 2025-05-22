/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aourhou <aourhou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:48:51 by aourhou           #+#    #+#             */
/*   Updated: 2025/05/22 15:48:52 by aourhou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

void	purge(t_game *g, int y)
{
	int	k;

	k = 0;
	while (k < y)
	{
		free(g->world_map[k]);
		k++;
	}
}

int	convert_char_map_to_int(t_game *g)
{
	int	y;
	int	x;

	y = 0;
	g->world_map = malloc(g->map_info->map_height * sizeof(int *));
	if (!g->world_map)
		return (1);
	while (y < g->map_info->map_height)
	{
		g->world_map[y] = malloc(g->map_info->map_width * sizeof(int));
		if (!g->world_map[y])
			return (purge(g, y), free(g->world_map), 1);
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

void	free_int_map(int **int_map, int height)
{
	int	y;

	y = 0;
	while (y < height)
	{
		free(int_map[y]);
		y++;
	}
	free(int_map);
}
