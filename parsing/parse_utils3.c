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

int is_map_start_line(char *line)
{
	while (*line)
	{
		if (*line == '1' || *line == '0' ||
		    *line == 'N' || *line == 'S' ||
		    *line == 'E' || *line == 'W')
			return (1);
		line++;
	}
	return (0);
}

void remove_new_line(char *line)
{
	if (!line)
		return;
	int len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	*d;

	if (dest == src)
		return (dest);
	if (!dest && !src)
		return (NULL);
	i = 0;
	s = (unsigned char *)src;
	d = (unsigned char *)dest;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*src;
	size_t			i;

	src = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		src[i] = (unsigned char)c;
		i++;
	}
	return (s);
}