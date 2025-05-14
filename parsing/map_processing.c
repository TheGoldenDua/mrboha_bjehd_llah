#include "../includes/cub3d.h"

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W');
}

int	get_max_width(char **map)
{
	int	max;
	int	len;
	int	i;

	i = 0;
	max = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > 0 && map[i][len - 1] == '\n')
			len--;
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

void	fill_line_spaces(char *line, int max_width)
{
	int	len;
	
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		len--;
	while (len < max_width)
	{
		line[len++] = ' ';
	}
	line[len] = '\0';
}

void	normalize_map(t_map *map)
{
	int	max_width;
	int	i;

	max_width = get_max_width(map->map_grid);
	i = 0;
	while (map->map_grid[i])
	{
		fill_line_spaces(map->map_grid[i], max_width);
		i++;
	}
}
