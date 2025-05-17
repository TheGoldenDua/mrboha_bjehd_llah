#include "../includes/cub3d.h"

int get_map_height(char **lines, int start)
{
	int height = 0;
	while (lines[start])
	{
		if (!is_line_empty(lines[start]))
			height++;
		start++;
	}
	return height;
}

int copy_real_map_lines(char **map_lines, int *index, t_map *map)
{
    int len = get_max_width(map_lines);
    int height = get_map_height(map_lines, *index);
    int j = 0;
    int i = *index;

    map->map_grid = malloc(sizeof(char *) * (height + 1));
    if (!map->map_grid)
        return print_error("Memory allocation failed", NULL);

    while (map_lines[i])
    {
        if (!is_line_empty(map_lines[i]))
        {
            map->map_grid[j] = fill_line_spaces(map_lines[i], len);
            if (!map->map_grid[j])
                return print_error("Line allocation failed", NULL);
            j++;
        }
        i++;
    }
    map->map_grid[j] = NULL;
    map->map_height = height;
    *index = i;
    return 0;
}


int get_map_info(char **map_lines,int *index, t_map *map)
{
	if (copy_real_map_lines(map_lines, index, map) == -1)
		return -1;
	if (validate_map(map) == -1)
		return -1;
	return 0;
}



