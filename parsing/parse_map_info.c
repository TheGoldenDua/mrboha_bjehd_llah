#include "../includes/cub3d.h"

int	get_map_height(char **lines, int start)
{
	int	height;

	height = 0;
	while (lines[start])
	{
		if (!is_line_empty(lines[start]))
			height++;
		start++;
	}
	return (height);
}

static int	fill_map_grid(char **map_lines, int *index, t_map *map, int len)
{
	int	i;
	int	j;

	i = *index;
	j = 0;
	while (map_lines[i])
	{
		if(!is_line_empty(map_lines[i]))
		{
			map->map_grid[j] = fill_line_spaces(map_lines[i], len);
			if (!map->map_grid[j])
				return (print_error("Line allocation failed", NULL));
			j++;
		}
		i++;
	}
	map->map_grid[j] = NULL;
	*index = i;
	return (0);
}

int	copy_real_map_lines(char **map_lines, int *index, t_map *map)
{
	int	len;
	int	height;

	len = get_max_width(map_lines);
	height = get_map_height(map_lines, *index);
	map->map_grid = malloc(sizeof(char *) * (height + 1));
	if (!map->map_grid)
		return (print_error("Memory allocation failed", NULL));
	if (fill_map_grid(map_lines, index, map, len) == -1)
		return (-1);
	map->map_height = height;
	return (0);
}

int	get_map_info(char **map_lines, int *index, t_map *map)
{
	if (copy_real_map_lines(map_lines, index, map) == -1)
		return (-1);
	if (validate_map(map) == -1)
		return (-1);
	return (0);
}
