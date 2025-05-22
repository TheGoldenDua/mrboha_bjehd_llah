/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aourhou <aourhou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:33:12 by del-ganb          #+#    #+#             */
/*   Updated: 2025/05/21 19:55:48 by aourhou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	init_data(t_map *map)
{
	map->n_wall = NULL;
	map->s_wall = NULL;
	map->w_wall = NULL;
	map->e_wall = NULL;
	map->ceiling_clr = -1;
	map->floor_clr = -1;
	map->map_grid = NULL;
	map->map_height = -1;
}

int	check_extension(char *s)
{
	int	len;

	len = ft_strlen(s);
	if (len < 4 || ft_strncmp(s + len - 4, ".cub", 4) != 0)
		return (-1);
	return (0);
}

void	ini_mlx(t_game *g, t_map *map)
{
	int	i;

	i = 0;
	g->world_map = NULL;
	g->img = NULL;
	g->win = NULL;
	g->map_info = map;
	g->mlx = NULL;
	while (i < NUM_TEXTURES)
	{
		g->tex_img[i] = NULL;
		i++;
	}
}

int	main(int ac, char **av)
{
	t_map	map;
	t_game	g;

	if (ac != 2)
		return (printf("Error\nIncorrect Parameters!\n"), 1);
	if (check_extension(av[1]) == -1)
		return (printf("Error\nInvalid File Extension\n"), 1);
	init_data(&map);
	if (parse_cub_file(av[1], &map) == -1)
		return (free_data(&map), 1);
	else
	{
		ini_mlx(&g, &map);
		if (big_bang(g) == 1)
			return (free_data(&map), cleanup(&g), 1);
	}
	free_data(&map);
	cleanup(&g);
	return (0);
}
