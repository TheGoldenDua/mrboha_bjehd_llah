#include "../includes/cub3d.h"

void	free_array(char ***arr)
{
	int	i;

	if (!arr || !*arr)
		return ;
	i = 0;
	while ((*arr)[i])
	{
		free((*arr)[i]);
		i++;
	}
	free(*arr);
	*arr = NULL;
}

void	free_wall(char **wall)
{
	if (*wall)
	{
		free(*wall);
		*wall = NULL;
	}
}

void	free_map_grid(char ***grid)
{
	int	i;

	if (!grid || !*grid)
		return ;
	i = 0;
	while ((*grid)[i])
	{
		free((*grid)[i]);
		i++;
	}
	free(*grid);
	*grid = NULL;
}

void	free_textures(t_map *map)
{
	if (map->n_wall)
		free(map->n_wall);
	if (map->s_wall)
		free(map->s_wall);
	if (map->w_wall)
		free(map->w_wall);
	if (map->e_wall)
		free(map->e_wall);
	map->n_wall = NULL;
	map->s_wall = NULL;
	map->w_wall = NULL;
	map->e_wall = NULL;
}

void	free_lines(char **lines)
{
	int	i;

	i = 0;
	if (!lines)
		return ;
	while (lines[i])
		free(lines[i++]);
	free(lines);
}
