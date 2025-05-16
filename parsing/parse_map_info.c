#include "../includes/cub3d.h"

int	count_real_map_lines(char **map_lines)
{
	int	height;
	int	count;

	height = 0;
	count = 0;
	while (map_lines[height])
	{
		if (!is_empty_line(map_lines[height]))
			count++;
		height++;
	}
	return (count);
}



// int	copy_real_map_lines(char **map_lines, t_map *map, int max_width)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (map_lines[i])
// 	{
// 		printf("Checking line: '%s'\n", map_lines[i]);
// 		if (!is_empty_line(map_lines[i]))
// 		{
// 			map->map_grid[j] = malloc(sizeof(char) * (max_width + 2));
// 			if (!map->map_grid[j])
// 				return (print_error("Memory allocation failed", map));
// 			ft_strlcpy(map->map_grid[j], map_lines[i], max_width + 2);
// 			printf("Storing line: '%s'\n", map_lines[i]);
// 			j++;
// 		}
// 		i++;
// 	}
// 	map->map_grid[j] = NULL;
// 	return (0);
// }

// int	get_map_info(char **map_lines, t_map *map)
// {
// 	int	real_height;
// 	int max_width;

// 	real_height = count_real_map_lines(map_lines);
// 	max_width = get_max_width(map_lines);
// 	map->map_grid = malloc(sizeof(char *) * (real_height + 1));
// 	if (!map->map_grid)
// 		return (print_error("Memory allocation failed", map));
// 	if (copy_real_map_lines(map_lines, map, max_width) == -1)
// 		return (-1);
//     if (!map->map_grid[0])
// 		return (print_error("No map found in the file", map));
//     normalize_map(map);
// 	if (validate_map(map) == -1)
// 		return (-1);
// 	return (0);

// int count_map_height(char **lines)
// {
// 	int count = 0;

// 	printf(">> count_map_height (safe version) CALLED\n");

// 	while (*lines)
// 	{
// 		if (**lines != '\0')  // Skip truly empty lines only
// 			count++;

// 		lines++;
// 	}
// 	printf(">> count_map_height FINAL COUNT: %d\n", count);
// 	return count;
// }

int ft_strlen_2d(char **strs)
{
	int i = 0;
	while (strs[i])
		i++;
	return i;
}

int count_map_height(char **lines)
{
	int count = 0;

	while (lines[count])
	{
		printf(">> count_map_height sees: \"%s\"\n", lines[count]);  // ✅ Add this
		count++;
	}

	printf(">> count_map_height FINAL COUNT: %d\n", count);
	return count;
}



int copy_real_map_lines(char **map_lines, t_map *map)
{
	int i = 0;
	int j = 0;
	int size = count_map_height(map_lines);

	printf(">>> DEBUG: count_map_height(map_lines) = %d\n", size);

	map->map_grid = malloc(sizeof(char *) * (size + 1));
	if (!map->map_grid)
		return print_error("Memory allocation failed", map);

	while (map_lines[i])
	{
		printf(">>> Line[%d]: \"%s\"\n", i, map_lines[i]);  // Add this line

		if (!is_empty_line(map_lines[i]))
		{
			map->map_grid[j] = ft_strdup(map_lines[i]);
			printf(">>> COPIED as map[%d]: \"%s\"\n", j, map->map_grid[j]);  // Confirm what got copied
			j++;
		}
		i++;
	}
	map->map_grid[j] = NULL;
	map->map_height = j;
	printf(">>> FINAL map->map_height = %d\n", map->map_height);
	return 0;
}


int get_map_info(char **map_lines, t_map *map)
{
	if (copy_real_map_lines(map_lines, map) == -1)
		return -1;
	normalize_map(map);
	if (validate_map(map) == -1)
		return -1;
	return 0;
}



