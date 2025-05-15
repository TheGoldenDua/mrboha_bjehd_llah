#include "../includes/cub3d.h"

// int validate_color_format(char *line)
// {
//     if (!line || (*line != 'F' && *line != 'C') ||
//     !(line[1] == ' ' || (line[1] >= 9 && line[1] <= 13)))
//         return (print_error("Invalid color identifier", NULL));
//     return (0);
// }

int	check_digit_and_range(char *str)
{
	int	i;
	int	value;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (print_error("RGB not digit", NULL));
		i++;
	}
	value = ft_atoi(str);
	if (value < 0 || value > 255)
		return (print_error("Wrong RGB", NULL));
	return (0);
}

int	validate_rgb_values(char **color, int comma_count)
{
	int		i;
	char	*trimmed;

	if (!color || !color[0] || !color[1] || !color[2]
		|| color[3] || comma_count != 2)
		return (free_array(&color),
			print_error("Wrong RGB Value", NULL));
	i = -1;
	while (color[++i])
	{
		trimmed = ft_strtrim(color[i], " \t\n\r");
		if (!trimmed)
			return (free_array(&color),
				print_error("Malloc error", NULL));
		if (check_digit_and_range(trimmed) == -1)
			return (free(trimmed), free_array(&color), -1);
		free(trimmed);
	}
	return (0);
}

int	is_file_content_empty(char **lines)
{
	int	j;
	int	x;

	j = 0;
	while (lines[j])
	{
		x = 0;
		while (lines[j][x])
		{
			if (lines[j][x] != ' ' && lines[j][x] != '\t'
				&& lines[j][x] != '\n' && lines[j][x] != '\r'
				&& lines[j][x] != '\v' && lines[j][x] != '\f')
				return (0);
			x++;
		}
		j++;
	}
	return (1);
}
