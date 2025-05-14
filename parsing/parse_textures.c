#include "../includes/cub3d.h"

int set_tex_path(char **texture, char *line)
{
    char *path = ft_strtrim(line + 2, " \t\n");
    if (ft_strchr(path, ' '))
    {
        free(path);
        return (print_error("Texture path contains invalid space", NULL), -1);
    }
    if (!path || path[0] == '\0')
    {
        free(path);
        return (print_error("Invalid texture path", NULL), -1);
    }

    if (*texture != NULL)
    {
        free(path);
        return (print_error("Texture defined more than once", NULL), -1);
    }

    *texture = path;

    return (0);
}


int parse_tex(char *line, t_map *map)
{
    if (line == NULL || ft_strlen(line) < 2)
        return 0;

    if (!ft_strncmp(line, "NO", 2) && (line[2] == ' ' || (line[2] >= 9 && line[2] <= 13)))
        return set_tex_path(&map->N_wall, line) == -1 ? -1 : 1;

    if (!ft_strncmp(line, "SO", 2) && (line[2] == ' ' || (line[2] >= 9 && line[2] <= 13)))
        return set_tex_path(&map->S_wall, line) == -1 ? -1 : 1;

    if (!ft_strncmp(line, "WE", 2) && (line[2] == ' ' || (line[2] >= 9 && line[2] <= 13)))
        return set_tex_path(&map->W_wall, line) == -1 ? -1 : 1;

    if (!ft_strncmp(line, "EA", 2) && (line[2] == ' ' || (line[2] >= 9 && line[2] <= 13)))
        return set_tex_path(&map->E_wall, line) == -1 ? -1 : 1;

    return 0;
}
