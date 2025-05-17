#include "../includes/cub3d.h"

int set_tex_path(char **texture, char *value)
{
    char *path = ft_strtrim(value, " \t\n");
    if (!path || path[0] == '\0')
    {
        free(path);
        return (print_error("Invalid texture path", NULL), -1);
    }
    if (ft_strchr(path, ' '))
    {
        free(path);
        return (print_error("Texture path contains invalid space", NULL), -1);
    }

    if (*texture != NULL)
    {
        free(path);
        return (print_error("Texture defined more than once", NULL), -1);
    }

    *texture = path;

    return (0);
}

int	handle_texture_identifier(t_map *map, char **tokens)
{
	if (!ft_strncmp(tokens[0], "NO", 3))
	{
		if (map->N_wall)
		{
			print_error("Texture NO defined more than once", NULL);
			return (-1);
		}
		return (set_tex_path(&map->N_wall, tokens[1]));
	}
	if (!ft_strncmp(tokens[0], "SO", 3))
	{
		if (map->S_wall)
		{
			print_error("Texture SO defined more than once", NULL);
			return (-1);
		}
		return (set_tex_path(&map->S_wall, tokens[1]));
	}
	if (!ft_strncmp(tokens[0], "WE", 3))
	{
		if (map->W_wall)
		{
			print_error("Texture WE defined more than once", NULL);
			return (-1);
		}
		return (set_tex_path(&map->W_wall, tokens[1]));
	}
	if (!ft_strncmp(tokens[0], "EA", 3))
	{
		if (map->E_wall)
		{
			print_error("Texture EA defined more than once", NULL);
			return (-1);
		}
		return (set_tex_path(&map->E_wall, tokens[1]));
	}
	return (-1);
}



// int	parse_tex(char *line, t_map *map)
// {
// 	int	i;

// 	i = 0;
// 	while (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
// 		i++;
// 	if (!ft_strncmp(&line[i], "NO", 2)
// 		&& (line[i + 2] == ' ' || (line[i + 2] >= 9 && line[i + 2] <= 13)))
// 		return (set_tex_path(&map->N_wall, &line[i]) == -1 ? -1 : 1);
// 	if (!ft_strncmp(&line[i], "SO", 2)
// 		&& (line[i + 2] == ' ' || (line[i + 2] >= 9 && line[i + 2] <= 13)))
// 		return (set_tex_path(&map->S_wall, &line[i]) == -1 ? -1 : 1);
// 	if (!ft_strncmp(&line[i], "WE", 2)
// 		&& (line[i + 2] == ' ' || (line[i + 2] >= 9 && line[i + 2] <= 13)))
// 		return (set_tex_path(&map->W_wall, &line[i]) == -1 ? -1 : 1);
// 	if (!ft_strncmp(&line[i], "EA", 2)
// 		&& (line[i + 2] == ' ' || (line[i + 2] >= 9 && line[i + 2] <= 13)))
// 		return (set_tex_path(&map->E_wall, &line[i]) == -1 ? -1 : 1);
// 	return (0);
// }

