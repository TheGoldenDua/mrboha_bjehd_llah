#include "../includes/cub3d.h"

int	copy_real_map_lines(char **map_lines,int *index, t_map *map)
{

	int j;
	int len;
	
	len = get_max_width(map_lines);
	j = 0;
	while(map_lines[*index])
	{
		printf("jama");
		if (!is_line_empty(map_lines[*index]))
		{
		
			fill_line_spaces(map_lines[*index], len, map->map_grid[j]);
			j++;
		}
		(*index)++;
	}
	return (0);
}


int ft_strlen_2d(char **strs)
{
	int i = 0;
	while (strs[i])
		i++;
	return i;
}

int get_map_info(char **map_lines,int *index, t_map *map)
{
	if (copy_real_map_lines(map_lines, index, map) == -1)
		return -1;
	// if (validate_map(map) == -1)
	// 	return -1;
	return 0;
}



