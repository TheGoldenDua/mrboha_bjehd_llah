#include "../includes/cub3d.h"

int	count_real_map_lines(char **map_lines)
{
	int	height;
	int	count;

	height = 0;
	count = 0;
	while (map_lines[height])
	{
		if (!is_empty_line(map_lines[height]))
			count++;
		height++;
	}
	return (count);
}

int	copy_real_map_lines(char **map_lines, t_map *map, int max_width)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map_lines[i])
	{
		if (!is_empty_line(map_lines[i]))
		{
			map->map_grid[j] = malloc(sizeof(char) * (max_width + 2));
			if (!map->map_grid[j])
				return (print_error("Memory allocation failed", map));
			ft_strlcpy(map->map_grid[j], map_lines[i], max_width + 2);
			j++;
		}
		i++;
	}
	map->map_grid[j] = NULL;
	return (0);
}

int	get_map_info(char **map_lines, t_map *map)
{
	int	real_height;
	int max_width;

	real_height = count_real_map_lines(map_lines);
	max_width = get_max_width(map_lines);
	map->map_grid = malloc(sizeof(char *) * (real_height + 1));
	if (!map->map_grid)
		return (print_error("Memory allocation failed", map));
	if (copy_real_map_lines(map_lines, map, max_width) == -1)
		return (-1);
    if (!map->map_grid[0])
		return (print_error("No map found in the file", map));
    normalize_map(map);
	if (validate_map(map) == -1)
		return (-1);
	return (0);
}

