#include "../includes/cub3d.h"

int	check_row_walls(char *row)
{
	int	i;

	i = 0;
	while (row[i])
	{
		if (row[i] == '\n')
		{
			i++;
			continue;
		}
		if (row[i] != '1' && row[i] != ' ' && row[i] != '\t')
			return (print_error("Map must be surrounded by walls", NULL));
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

int	check_space_surroundings(char **map)
{
	int msize;
	int width;
	int x;
	int y;

	
	y = 0;
	msize = count_real_map_lines(map);
	while(y < msize - 1)
	{
		x = 0;
		width = ft_strlen(map[y]);
		while(x < width)
		{
			if (map[y][x] == '0')
			{
				if (map[y - 1][x] == ' ' || map[y][x + 1] == ' ' || map[y + 1][x] == ' ' || map[y][x - 1] == ' ')
					return (print_error("Invalid inner map", NULL));
			}
			x++;
		}
		y++;
	}
	return 0;
}	


