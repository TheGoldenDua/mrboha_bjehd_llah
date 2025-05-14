#include "../includes/cub3d.h"

int count_lines(int fd)
{
    char *line;
    char *trimmed;
    int count = 0;
    while ((line = get_next_line(fd)))
    {
        trimmed = ft_strtrim(line, " \t\r\n");
        if (!trimmed)
        {
            free(line);
            return (print_error("malloc failed in count_lines", NULL), -1);
        }
        if (*trimmed != '\0')
            count++;
        free(trimmed);
        free(line);
    }
    if (count == 0)
        return(print_error("empty file", NULL), -1);
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
    if (size == 0)
        return NULL;
    lines = malloc(sizeof(char *) * (size )); 
    fd = open(file, O_RDONLY);
    while ((line = get_next_line(fd)))
    {
        lines[count++] = ft_strdup(line);
        if(!lines)
            return NULL;
        free(line);
    }
    lines[count] = NULL;
    return (lines);
}


int	parse_identifiers(char **file_content, t_map *map, int *i)
{
    int res;
	int parsed_any = 0;

    while (file_content[*i] && !is_map_line(file_content[*i]))
    {
        char *line = file_content[*i];
        if (is_empty_line(line))
        {
            (*i)++;
            continue;
        }

        res = parse_tex(line, map);
        if (res == -1)
            return ( -1);
        if (res == 1)
        {
            (*i)++;
			parsed_any = 1;
            continue;
        }
        if ((line[0] == 'F' || line[0] == 'C') && line[1] == ' ')
        {
            if (set_color(line, map) == -1)
                return ( -1);
			parsed_any = 1;
            (*i)++;
            continue;
        }
        return (print_error("Invalid identifier", map));
    }

	if (!parsed_any)
    return print_error("Map must appear after identifiers", map), -1;

    if (check_all_identifiers(map) == -1)
        return ( -1);

    return (0);
}

int	parse_cub_file(char *file, t_map *map)
{
	// init_data(map);
	int		fd;
	char	**file_content;
	int		i;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (print_error("Could not open file", NULL));
	file_content = read_all_lines(file, fd);
	close(fd);
	i = 0;
	if (parse_identifiers(file_content, map, &i) == -1)
	{
		free_data(map);               
		free_lines(file_content);     
		return (-1);
	}
	while (file_content[i] && is_empty_line(file_content[i]))
		i++;
	if (!file_content[i])
		return (free_lines(file_content),
			print_error("No map found in the file", map));
	if (get_map_info(file_content + i, map) == -1)
		return (free_lines(file_content), -1);
	free_lines(file_content);
	return (0);
}