#include "../includes/cub3d.h"

int	has_valid_border(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if (!map || !map[0])
		return (print_error("Map is empty", NULL));
	if (check_row_walls(map[0]) == -1)
		return (-1);
	while (map[i])
		i++;
	if (check_row_walls(map[i - 1]) == -1)
		return (-1);
	while (j < i - 1)
	{
		if (check_side_walls(map[j]) == -1)
			return (-1);
		j++;
	}
	return (0);
}

static int	scan_map_line(char *line, int y, int *count, t_map *data)
{
	int		x;
	char	c;

	x = 0;
	while (line[x])
	{
		c = line[x];
		if (!is_valid_char(c))
			return (print_error("Invalid character in map", data));
		if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		{
			data->player_x = x;
			data->player_y = y;
			data->player_dir = c;
			(*count)++;
		}
		x++;
	}
	return (0);
}

int	player_count_and_pos(char **map, t_map *data)
{
	int	y;
	int	count;

	y = 0;
	count = 0;
	while (map[y])
	{
		if (scan_map_line(map[y], y, &count, data) == -1)
			return (-1);
		y++;
	}
	if (count == 0)
		return (print_error("Map missing a player", data));
	if (count > 1)
		return (print_error("Map has more than one player", data));
	return (0);
}

int	validate_map(t_map *map)
{
	if (!map->map_grid)
		return (print_error("Map block not found after identifiers", map));
	if (has_valid_border(map->map_grid))
		return (1);
	if (player_count_and_pos(map->map_grid, map))
		return (1);
	if (check_space_surroundings(map))
		return (1);
	return (0);
}
