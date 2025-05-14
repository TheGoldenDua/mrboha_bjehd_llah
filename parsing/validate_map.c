#include "../includes/cub3d.h"

// int	is_map_whitespace_only(char **map)
// {
// 	int	y;
// 	int	x;

// 	y = 0;
// 	while (map[y])
// 	{
// 		x = 0;
// 		while (map[y][x])
// 		{
// 			if (map[y][x] != ' ' && map[y][x] != '\t'
// 				&& map[y][x] != '\n' && map[y][x] != '\r'
// 				&& map[y][x] != '\v' && map[y][x] != '\f')
// 				return (0);
// 			x++;
// 		}
// 		y++;
// 	}
// 	return (1);
// }

int	check_minimum_elements(char **map)
{
	int	y;
	int	x;
	int	has_wall;
	int	has_player;

	y = 0;
	has_wall = 0;
	has_player = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				has_wall = 1;
			if (map[y][x] == 'N' || map[y][x] == 'S'
				|| map[y][x] == 'E' || map[y][x] == 'W')
				has_player = 1;
			x++;
		}
		y++;
	}
	if (!has_wall)
		return (print_error("Map has no walls", NULL));
	if (!has_player)
		return (print_error("Map has no player", NULL));
	return (0);
}

int	has_valid_border(char **map)
{
	int	i;

	if (check_row_walls(map[0]))
		return (1);
	i = 0;
	while (map[i])
		i++;
	if (check_row_walls(map[i - 1]))
		return (1);
	i = 0;
	while (map[i])
	{
		if (check_side_walls(map[i]))
			return (1);
		i++;
	}
	return (0);
}

int	player_count_and_pos(char **map, t_map *data)
{
	int	x, y, count;
	char	c;

	y = 0;
	count = 0;
	while (map[y])
	{
		x = 0;
		while ((c = map[y][x]))
		{
			if (!is_valid_char(c))
				return (print_error("Invalid character in map", data));
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				data->player_x = x;
				data->player_y = y;
				data->player_dir = c;
				count++;
			}
			x++;
		}
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
	// if (is_map_whitespace_only(map->map_grid))
	// 	return (print_error("Map is empty or only contains whitespace", map));
	if (check_minimum_elements(map->map_grid))
		return (1);
	if (has_valid_border(map->map_grid))
		return (1);
	if (check_space_surroundings(map->map_grid))
		return (1);
	if (player_count_and_pos(map->map_grid, map))
		return (1);
	// if (check_enclosure(map->map_grid))
	// // 	return (1);
	return (0);
}
