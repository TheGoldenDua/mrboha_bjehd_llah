
#include "../includes/cub3d.h"

void	free_array(char ***arr)
{
	int	i;

	if (!arr || !*arr)
		return;
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
		return;
	i = 0;
	while ((*grid)[i])
	{
		free((*grid)[i]);
		i++;
	}
	free(*grid);
	*grid = NULL;
}

void	free_data(t_map *map)
{
	if (!map)
		return ;
	free_wall(&map->N_wall);
	free_wall(&map->S_wall);
	free_wall(&map->W_wall);
	free_wall(&map->E_wall);
	free_array(&map->Floor_clr);
	free_array(&map->Ceiling_clr);
	free_map_grid(&map->map_grid);
}

void free_lines(char **lines)
{
	int i = 0;
	while (lines[i])
		free(lines[i++]);
	free(lines);
}
