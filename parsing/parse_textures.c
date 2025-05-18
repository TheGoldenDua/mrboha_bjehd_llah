#include "../includes/cub3d.h"

int	check_tex_extension(char *s)
{
	int	len;
	int	i;

	len = ft_strlen(s);
	if (len < 4 || ft_strncmp(s + len - 4, ".xpm", 4) != 0)
		return (-1);
	i = 0;
	while (i < len - 4)
	{
		if (s[i] == '.' && s[i + 1] == '.')
			return (-1);
		i++;
	}
	return (0);
}

int	set_tex_path(char **texture, char *value)
{
	char	*path;

	path = ft_strtrim(value, " \t\n");
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
	if (check_tex_extension(path) == -1)
	{
		free(path);
		return (print_error("Invalid texture path extension", NULL), -1);
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
		if (map->n_wall)
			return (print_error("Texture NO defined more than once", NULL));
		return (set_tex_path(&map->n_wall, tokens[1]));
	}
	if (!ft_strncmp(tokens[0], "SO", 3))
	{
		if (map->s_wall)
			return (print_error("Texture SO defined more than once", NULL));
		return (set_tex_path(&map->s_wall, tokens[1]));
	}
	if (!ft_strncmp(tokens[0], "WE", 3))
	{
		if (map->w_wall)
			return (print_error("Texture WE defined more than once", NULL));
		return (set_tex_path(&map->w_wall, tokens[1]));
	}
	if (!ft_strncmp(tokens[0], "EA", 3))
	{
		if (map->e_wall)
			return (print_error("Texture EA defined more than once", NULL));
		return (set_tex_path(&map->e_wall, tokens[1]));
	}
	return (-1);
}
