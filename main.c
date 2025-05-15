#include "includes/cub3d.h"

void	init_data(t_map *map)
{
    map->N_wall = NULL;
    map->S_wall = NULL;
    map->W_wall = NULL;
    map->E_wall = NULL;
    map->Ceiling_clr = -1;
    map->Floor_clr = -1;
    map->map_grid = NULL;
}

int	check_extension(char *s)
{
	int	len;

	len = ft_strlen(s);
	if (len < 4 || ft_strncmp(s + len - 4, ".cub", 4) != 0)
		return (1);
	return (0);
}

int main(int ac, char **av)
{
    t_map map;
    
    if (ac != 2)
        return (printf("Error\n Incorrect Parameters!\n Usage: ./cub3d <map_file.cub>\n"), 1);
    if(check_extension(av[1]) == 1)
        return (printf("Error\n Invalid File Extension\n Correct Extention: <file.cub> \n"), 1);
    init_data(&map);
    if (parse_cub_file(av[1], &map) == -1)
        return(1);
    free_data(&map);
    return (EXIT_SUCCESS);
}
