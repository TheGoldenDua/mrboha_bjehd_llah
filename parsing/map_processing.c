#include "../includes/cub3d.h"

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W');
}

int	get_max_width(char **map)
{
	int i;
	int current_len;
	int max_len;

	i = 0;
	current_len = 0;
	max_len = 0;
	while (map[i])
	{
		current_len = ft_strlen(map[i]);
		if (current_len >= max_len)
			max_len = current_len;
		i++;
	}
	return (max_len);
}

void fill_line_spaces(char *line, int max_width, char *map)
{
	int i;
	int j;

	i = 0;
	j = 0;
	map = malloc(sizeof(char *) * max_width + 1);
	while(line[i])
	{
		map[i] = line[i];
		i++;
	}
	if (i < max_width)
	{
		while(i < max_width)
		{
			map[i] = ' ';
			i++;
		}
	}
	map[i] = '\0';
	printf("%s\n", map);
}

