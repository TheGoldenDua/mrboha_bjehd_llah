#include "includes/cub3d.h"

void	init_data(t_map *map)
{
	map->n_wall = NULL;
	map->s_wall = NULL;
	map->w_wall = NULL;
	map->e_wall = NULL;
	map->ceiling_clr = -1;
	map->floor_clr = -1;
	map->map_grid = NULL;
	map->map_height = -1;
}

int	check_extension(char *s)
{
	int	len;

	len = ft_strlen(s);
	if (len < 4 || ft_strncmp(s + len - 4, ".cub", 4) != 0)
		return (-1);
	return (0);
}

int	main(int ac, char **av)
{
	t_map	map;

	if (ac != 2)
	{
		print_error("Incorrect Parameters!\n Usage: ./cub3d <map_file.cub>",
			NULL);
		return (1);
	}
	if (check_extension(av[1]) == -1)
	{
		print_error("Invalid File Extension\n Correct Extention: <file.cub>",
			NULL);
		return (1);
	}
	init_data(&map);
	if (parse_cub_file(av[1], &map) == -1)
		return (free_data(&map), 1);
	free_data(&map);
	return (0);
}
