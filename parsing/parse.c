#include "../includes/cub3d.h"

int count_lines(int fd)
{
    char *line;
    char *trimmed = NULL;  // ✅ initialized to avoid warnings
    int count = 0;

    while ((line = get_next_line(fd)))
    {
        remove_new_line(line);  // ✅ removes only the newline

        trimmed = ft_strtrim(line, " \t\r");  // ✅ removes whitespace ends
        if (!trimmed)
        {
            free(line);
            return (print_error("malloc failed in count_lines", NULL), -1);
        }

        if (*trimmed != '\0')  // ✅ only count if real content exists
            count++;

        free(trimmed);
        free(line);
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
    lines = malloc(sizeof(char *) * (size + 1 )); 
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


// int	parse_identifiers(char **file_content, t_map *map, int *i)
// {
//     int res;
// 	int parsed_any = 0;

//     while (file_content[*i] && !is_map_line(file_content[*i]))
//     {
//         char *line = file_content[*i];
//         if (is_empty_line(line))
//         {
//             (*i)++;
//             continue;
//         }
        
//         res = parse_tex(line, map);
//         if (res == -1)
//             return ( -1);
//         if (res == 1)
//         {
//             (*i)++;
// 			parsed_any = 1;
//             continue;
//         }
//         if ((line[0] == 'F' || line[0] == 'C') && line[1] == ' ')
//         {
//             if (set_color(line, map) == -1)
//                 return ( -1);
// 			parsed_any = 1;
//             (*i)++;
//             continue;
//         }
//         return (print_error("Invalid identifier", map));
//     }

// 	if (!parsed_any)
//     return print_error("Map must appear after identifiers", map), -1;

//     if (check_all_identifiers(map) == -1)
//         return ( -1);

//     return (0);
// }

// int	parse_cub_file(char *file, t_map *map)
// {
// 	// init_data(map);
// 	int		fd;
// 	char	**file_content;
// 	int		i;

// 	fd = open(file, O_RDONLY);
// 	if (fd < 0)
// 		return (print_error("Could not open file", NULL));
// 	file_content = read_all_lines(file, fd);
// 	close(fd);
//     if (!file_content)
// 	    return (print_error("Empty or invalid file", map), -1);
// 	i = 0;
// 	if (parse_identifiers(file_content, map, &i) == -1)
// 	{
// 		free_data(map);               
// 		free_lines(file_content);     
// 		return (-1);
// 	}
// 	while (file_content[i] && is_empty_line(file_content[i]))
// 		i++;
// 	if (!file_content[i])
// 		return (free_lines(file_content),
// 			print_error("No map found in the file", map));
// 	if (get_map_info(file_content + i, map) == -1)
// 		return (free_lines(file_content), -1);
// 	free_lines(file_content);
// 	return (0);
// }

int is_valid_identifier(t_map *map, char **token)
{
    if(ft_strncmp(token[0], "NO", 3) == 0 && !map->N_wall)
        return (set_tex_path(&map->N_wall, token[1]), 0);
    else if(ft_strncmp(token[0], "SO", 3) == 0 && !map->S_wall)
        return (set_tex_path(&map->S_wall, token[1]), 0);
    else if(ft_strncmp(token[0], "WE", 3) == 0 && !map->W_wall)
        return (set_tex_path(&map->W_wall, token[1]), 0);
    else if(ft_strncmp(token[0], "EA", 3) == 0 && !map->E_wall)
        return (set_tex_path(&map->E_wall, token[1]), 0);
    else if(ft_strncmp(token[0], "F", 2) == 0 && map->Floor_clr == -1)
        return (set_color(&map->Floor_clr, token[1]), 0);
    else if(ft_strncmp(token[0], "C", 2) == 0 && map->Ceiling_clr == -1)
        return (set_color(&map->Ceiling_clr, token[1]), 0);
    else
        return (-1);
}

int	parse_cub_file(char *file, t_map *map)
{
	int		fd;
	char	**file_content;
    char **tokens;
    char  *line;
	int		i;
    int count;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (print_error("Could not open file", NULL), -1);
	file_content = read_all_lines(file, fd);
	close(fd);
    i = 0;
    count = 0;
    while(file_content[i] && count < 6)
    {
        line = ft_strtrim(file_content[i], "\t\n\r");
        if (!line || line[0] == '\0')
        {
            free(line);
            i++;
            continue;
        }
        tokens = ft_split(line, ' ');
        if(!tokens || !tokens[0] || !tokens[1] || tokens[2])
            return (free_lines(file_content), free(line), free_split(tokens), free_textures(map), print_error("poblem in identifiers!", NULL), -1);
        if(is_valid_identifier(map, tokens) == -1)
            return (free_lines(file_content), free(line), free_split(tokens), free_textures(map), print_error("Invalid identifier!", NULL), -1);
        else
            count++;
        free(line);
        free_split(tokens);
        i++;
    }
    if(count != 6)
        return (free_lines(file_content) ,print_error("Missing an identifier!", map),-1);
    while (file_content[i] && is_empty_line(file_content[i]))
        i++;
    if (!file_content[i])
        return (free_lines(file_content) ,print_error("No map found in the file", map), -1);
    // printf("Starting map parsing at line index: %d\n", i);
    printf(">>> DEBUG: parse_cub_file - starting at line index: %d\n", i);
    if (get_map_info(file_content + i, map) == -1)
        return (free_lines(file_content), -1);
    free_lines(file_content);
	return (0);
}