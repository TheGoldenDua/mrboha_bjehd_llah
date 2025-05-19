#include "../includes/cub3d.h"

int	check_row_walls(char *row)
{
	int	i;

	i = 0;
	while (row[i] && (row[i] == ' ' || row[i] == '\t'))
		i++;
	while (row[i])
	{
		if (row[i] == ' ' || row[i] == '\t')
		{
			i++;
			continue ;
		}
		if (row[i] != '1')
			return (print_error("Top or bottom border must be walls", NULL));
		i++;
	}
	return (0);
}

int	check_side_walls(char *row)
{
	int	start;
	int	end;

	start = 0;
	while (row[start] == ' ' || row[start] == '\t')
		start++;
	end = ft_strlen(row) - 1;
	while (end > 0 && (row[end] == ' ' || row[end] == '\t'))
		end--;
	if (row[start] != '1' || row[end] != '1')
		return (print_error("Map sides must be walls", NULL));
	return (0);
}

static int	is_invalid_surrounding(t_map *map, int x, int y)
{
	if ((int)ft_strlen(map->map_grid[y - 1]) <= x
		|| map->map_grid[y - 1][x] == ' '
		|| (int)ft_strlen(map->map_grid[y + 1]) <= x
		|| map->map_grid[y + 1][x] == ' '
		|| map->map_grid[y][x + 1] == ' '
		|| map->map_grid[y][x - 1] == ' ')
		return (1);
	return (0);
}

int	check_space_surroundings(t_map *map)
{
	int	y;
	int	x;
	int	width;

	y = 1;
	while (y < map->map_height - 1)
	{
		x = 1;
		width = ft_strlen(map->map_grid[y]);
		while (x < width - 1)
		{
			if (map->map_grid[y][x] == '0'
				&& is_invalid_surrounding(map, x, y))
				return (print_error("Invalid space near open area", NULL));
			x++;
		}
		y++;
	}
	return (0);
}
