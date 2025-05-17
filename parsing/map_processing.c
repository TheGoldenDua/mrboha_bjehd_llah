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

char *fill_line_spaces(const char *line, int max_width)
{
    int     i;
    char    *padded_line;

    padded_line = malloc(sizeof(char) * (max_width + 1));
    if (!padded_line)
        return (NULL); // Handle malloc failure

    i = 0;
    while (line[i])
    {
        padded_line[i] = line[i];
        i++;
    }
    while (i < max_width)
    {
        padded_line[i] = ' ';
        i++;
    }
    padded_line[i] = '\0';
    return (padded_line);
}


