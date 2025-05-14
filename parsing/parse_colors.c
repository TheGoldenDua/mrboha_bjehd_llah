#include "../includes/cub3d.h"

int	set_ceiling_color(t_map *map, char **color)
{
	if (map->Ceiling_clr)
	{
		free_array(&color);
		return (print_error("Ceiling color defined more than once", map));
	}
	map->Ceiling_clr = color;
	return (0);
}

int	set_floor_color(t_map *map, char **color)
{
	if (map->Floor_clr)
	{
		free_array(&color);
		return (print_error("Floor color defined more than once", map));
	}
	map->Floor_clr = color;
	return (0);
}

int	set_color(char *line, t_map *map)
{
	char	**color;
	char	*trimmed;
	int		comma_count;
	int		i;

	if (validate_color_format(line))
		return (print_error("Invalid color identifier", map), -1);
	trimmed = line + 1;
	while (*trimmed == ' ' || (*trimmed >= 9 && *trimmed <= 13))
		trimmed++;
	color = ft_split(trimmed, ',');
	if (!color)
		return (print_error("Color split failed", map), -1);
	comma_count = 0;
	i = -1;
	while (trimmed[++i])
		if (trimmed[i] == ',')
			comma_count++;
	if (validate_rgb_values(color, comma_count))
	{
        color = NULL;
        return (-1);
    }
	if (line[0] == 'C')
		return (set_ceiling_color(map, color));
	else if (line[0] == 'F')
		return (set_floor_color(map, color));
	else
		return (print_error("Unknown color identifier", map), -1);
}
