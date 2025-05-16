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

// void	fill_line_spaces(char *line, int max_width)
// {
// 	int	len;
	
// 	len = ft_strlen(line);
// 	if (len > 0 && line[len - 1] == '\n')
// 		len--;
// 	while (len < max_width)
// 	{
// 		line[len++] = ' ';
// 	}
// 	line[len] = '\0';
// }

// void	*ft_memset(void *s, int c, size_t n)
// {
// 	unsigned char	*src;
// 	size_t			i;

// 	src = (unsigned char *)s;
// 	i = 0;
// 	while (i < n)
// 	{
// 		src[i] = (unsigned char)c;
// 		i++;
// 	}
// 	return (s);
// }



void normalize_map(t_map *map)
{
	int max_width = get_max_width(map->map_grid);
	int i = 0;
	char *padded;
	size_t len;

	while (map->map_grid[i])
	{
		len = ft_strlen(map->map_grid[i]);
		padded = malloc(max_width + 1);
		if (!padded)
		{
			print_error("Memory allocation failed during normalization", map);
			return;
		}
		ft_memset(padded, ' ', max_width);
		ft_memcpy(padded, map->map_grid[i], len);
		padded[max_width] = '\0';

		free(map->map_grid[i]);
		map->map_grid[i] = padded;
		i++;
	}
}

