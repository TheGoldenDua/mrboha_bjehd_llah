#include "../includes/cub3d.h"

// int	check_row_walls(char *row)
// {
// 	int	i;

// 	i = 0;
// 	while(row[i] == ' ' || row[i] == '	')
// 		i++;
// 	while (row[i])
// 	{
// 		if (row[i] == '\n')
// 		{
// 			i++;
// 			continue;
// 		}
// 		if (row[i] != '1' && row[i] != ' ' && row[i] != '\t')
// 			return (print_error("Map must be surrounded by walls", NULL));
// 		i++;
// 	}
// 	return (0);
// }

int check_row_walls(char *row)
{
    int i = 0;
	// printf("Checking border row: %s\n", row);

    // Skip leading spaces/tabs
    while (row[i] && (row[i] == ' ' || row[i] == '\t'))
        i++;

    // Check that only '1' appears from here on
    while (row[i])
    {
        if (row[i] == ' ' || row[i] == '\t')
        {
            i++;
            continue;
        }
        if (row[i] != '1')
		{
			printf("Invalid char in border: '%c' (int: %d)\n", row[i], row[i]);
            return print_error("Top or bottom border must be walls", NULL);
		}
		i++;
    }
    return 0;
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

// int	is_out_of_bounds(char **map, int x, int y)
// {
// 	if (y < 0 || map[y] == NULL || x < 0 || x >= (int)ft_strlen(map[y]))
// 		return (1);
// 	return (0);
// }

// int	is_valid_neighbor(char c)
// {
// 	return (c == '1' || c == ' ');
// }	

int check_space_surroundings(t_map *map)
{
	int y = 1;
	int x, width;
	int msize = map->map_height;

	printf("sur: %d\n", msize);

	while (y < msize - 1)
	{
		x = 1;
		width = ft_strlen(map->map_grid[y]);
		while (x < width - 1)
		{
			if (map->map_grid[y][x] == '0')
			{
				if ((int)ft_strlen(map->map_grid[y - 1]) <= x || map->map_grid[y - 1][x] == ' ' ||
					(int)ft_strlen(map->map_grid[y + 1]) <= x || map->map_grid[y + 1][x] == ' ' ||
					map->map_grid[y][x + 1] == ' ' || map->map_grid[y][x - 1] == ' ')
					return print_error("Invalid space near open area", NULL);
			}
			x++;
		}
		y++;
	}
	return 0;
}

