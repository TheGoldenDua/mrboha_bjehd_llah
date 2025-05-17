#include "../includes/cub3d.h"

int	handle_color_identifier(t_map *map, char **tokens)
{
	if (!ft_strncmp(tokens[0], "F", 2))
	{
		if (map->Floor_clr != -1)
		{
			print_error("Floor color defined more than once", NULL);
			return (-1);
		}
		return (set_color(&map->Floor_clr, tokens[1]));
	}
	if (!ft_strncmp(tokens[0], "C", 2))
	{
		if (map->Ceiling_clr != -1)
		{
			print_error("Ceiling color defined more than once", NULL);
			return (-1);
		}
		return (set_color(&map->Ceiling_clr, tokens[1]));
	}
	return (-1);
}


int set_color(int *color_field, char *value)
{
	char **color;
	int r, g, b;
	int count;
	int i;

	count = 0;
	i = 0;
	if(*color_field != -1)
		return (print_error("Color defined more than once", NULL), -1);
	while (value[i])
	{
		if (value[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
		return (print_error("Invalid color format: must contain exactly two commas", NULL), -1);
	color = ft_split(value, ',');
	if(validate_rgb_values(color, 2) == -1)
		return (-1);
	r = ft_atoi(color[0]);
	g = ft_atoi(color[1]);
	b = ft_atoi(color[2]);
	*color_field = (r << 16) | (g << 8) | b;
	free_split(color);
	return (0);
}