#include "../includes/cub3d.h"

int count_lines(int fd)
{
    char *line;
    int count = 0;

    while ((line = get_next_line(fd)))
    {
        remove_new_line(line);
        free(line);
        count++;
    }
    if (count == 0)
        return -1;

    return count;
}


char **read_all_lines(char *file , int fd)
{
    char    **lines;
    char    *line;
    int     count;
    int     size;

    count = 0;
    size = count_lines(fd);
    close(fd);
    if (size <= 0)
        return NULL;
    lines = (char **)malloc(sizeof(char *) * (size + 1)); 
    if (!lines)
	    return NULL;
    fd = open(file, O_RDONLY);
    while ((line = get_next_line(fd)))
    {
        if (count >= size)
        {    
            free(line);
            break;
        }
        lines[count++] = ft_strdup(line);
        remove_new_line(lines[count - 1]);
        if (!lines[count - 1])
			return NULL;
        free(line);
    }
    lines[count] = NULL;
    return (lines);
}
int is_valid_identifier(t_map *map, char *token)
{
    char **tokens = ft_split(token, ' ');
    int result = -1;

    if (!tokens || !tokens[0] || !tokens[1])
        return (free_array(&tokens), -1);

    if (ft_strncmp(tokens[0], "NO", 3) == 0 && !map->N_wall)
        result = set_tex_path(&map->N_wall, tokens[1]);
    else if (ft_strncmp(tokens[0], "SO", 3) == 0 && !map->S_wall)
        result = set_tex_path(&map->S_wall, tokens[1]);
    else if (ft_strncmp(tokens[0], "WE", 3) == 0 && !map->W_wall)
        result = set_tex_path(&map->W_wall, tokens[1]);
    else if (ft_strncmp(tokens[0], "EA", 3) == 0 && !map->E_wall)
        result = set_tex_path(&map->E_wall, tokens[1]);
    else if (ft_strncmp(tokens[0], "F", 2) == 0 && map->Floor_clr == -1)
        result = set_color(&map->Floor_clr, tokens[1]);
    else if (ft_strncmp(tokens[0], "C", 2) == 0 && map->Ceiling_clr == -1)
        result = set_color(&map->Ceiling_clr, tokens[1]);
    free_array(&tokens);
    return (result);
}

int	is_line_empty(const char *line)
{
	while (*line)
	{
		if (!(*line == ' ' || *line == '\t' || *line == '\n'))
			return (0);
		line++;
	}
	return (1);
}

int	parse_cub_file(char *file, t_map *map)
{
	int		fd;
	char	**file_content;
	int		i;
    int     count;

    i = 0;
    count = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (print_error("Could not open file", NULL), -1);
	file_content = read_all_lines(file, fd);
    while(file_content[i] != NULL && count < 6)
    {
        if (!is_line_empty(file_content[i]))
        {
            is_valid_identifier(map, file_content[i]);
            count++;
        }
        i++;
    }
    count = 0;
    int index = 0;
    index = i;
    while(file_content[i] != NULL)
    {
        if (!is_line_empty(file_content[i]))
            count++;
        i++;
    }
    // map->map_grid = (char **)malloc(sizeof(char *) * count + 1);
    if (get_map_info(file_content, &index, map) == -1)
    {
        return (free_lines(file_content), -1);
    }
	close(fd);
	return (free_lines(file_content), 0);
}

