#include "../includes/cub3d.h"



int set_color(int *color_field, char *value)
{
	char **color;
	int r, g, b;

	if(*color_field != -1)
		return (print_error("Color defined more than once", NULL), -1);
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