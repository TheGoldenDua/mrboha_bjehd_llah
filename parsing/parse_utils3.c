#include "../includes/cub3d.h"

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

	if (!color || !color[0] || !color[1] || !color[2] || color[3]
		|| comma_count != 2)
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
	unsigned char *src;
	size_t i;

	src = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		src[i] = (unsigned char)c;
		i++;
	}
	return (s);
}