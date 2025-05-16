#include "../includes/cub3d.h"

int	check_all_identifiers(t_map *map)
{
	if (!map->N_wall || !map->S_wall || !map->W_wall || !map->E_wall)
		return (print_error("Missing texture identifier", map));
	if (!map->Floor_clr || !map->Ceiling_clr)
		return (print_error("Missing color identifier", map));
	return (0);
}

int	is_map_line(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (*line == '1' || *line == '0');
}

int is_empty_line(const char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n' && *line != '\r')
			return 0;  // Line contains visible content
		line++;
	}
	return 1;  // Line is only whitespace
}


int print_error(char *msg, t_map *map)
{
    printf("Error\n%s\n", msg);
    free_data(map);
    return (-1);
}

int	is_set(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}