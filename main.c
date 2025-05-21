/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aourhou <aourhou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:33:12 by del-ganb          #+#    #+#             */
/*   Updated: 2025/05/21 15:20:40 by aourhou          ###   ########.fr       */
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

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

// Returns a newly allocated int** array.
// The caller must free the returned array with free_int_map.


// Helper: Free the int map

// void mix_textures(t_game *g, t_map map)
// {
// 	g->files[0] = map.n_wall;
// 	g->files[1] = map.s_wall;
// 	g->files[2] = map.w_wall;
// 	g->files[3] = map.e_wall;
// }
// int	ft_merge(t_map *data, t_game *g)
// {
// 	g->map_int = convert_char_map_to_int(data->map_grid, data->map_height, data->map_width);
// 	if (!g->map_int)
// 		return (-1);
// 	mix_textures(g, data);
// 	g->ceiling_color = data->ceiling_clr;
// 	g->floor_color = data->floor_clr;
// 	g->map_h = data->map_height;
// 	g->map_w = data->map_width;

// 	return (0);
// }


// #include "mlx.h"
#include <stdlib.h>

void free_mlx_resources(t_game *g)
{
    // Destroy images (if you have multiple, destroy them all)
    if (g->img)
    {
        mlx_destroy_image(g->mlx, g->img);
        g->img = NULL;
    }

    // Free texture images if you use them
    for (int i = 0; i < NUM_TEXTURES; i++)
    {
        if (g->tex_img[i])
        {
            mlx_destroy_image(g->mlx, g->tex_img[i]);
            g->tex_img[i] = NULL;
        }
    }

    // Destroy window
    if (g->win)
    {
        mlx_destroy_window(g->mlx, g->win);
        g->win = NULL;
    }

    // Destroy display (Linux only, otherwise this is a no-op)
#ifdef __linux__
    if (g->mlx)
        mlx_destroy_display(g->mlx);
#endif

    // Free mlx pointer itself (if dynamically allocated, as on Linux)
    if (g->mlx)
    {
        free(g->mlx);
        g->mlx = NULL;
    }
}
void ini_mlx(t_game *g)
{
	int i;

	i = 0;
	while (i < NUM_TEXTURES)
	{
    	g->tex_img[i] = NULL;
		i++;
	}
}
int	main(int ac, char **av)
{
	t_map	map;
	t_game g;
	

	if (ac != 2)
	{
		print_error("Incorrect Parameters!\n Usage: ./cub3d <map_file.cub>",
			NULL);
		return (1);
	}
	if (check_extension(av[1]) == -1)
	{
		print_error("Invalid File Extension\n Correct Extention: <file.cub>",
			NULL);
		return (1);
	}
	init_data(&map);
	if (parse_cub_file(av[1], &map) == -1)
	{
		free_data(&map);
		return (1);
	}
	else
	{
;
		g.world_map = NULL;
		g.img = NULL;
		g.win = NULL;
		g.map_info = &map;
		g.mlx = NULL;
		ini_mlx(&g);
		big_bang(g);
		// free_mlx_resources(&g);
	}
	free_textures(&map);
	free_data(&map);
	cleanup(&g);
	return (0);
}
