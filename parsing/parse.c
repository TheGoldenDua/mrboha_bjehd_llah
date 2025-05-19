#include "../includes/cub3d.h"

char	**alloc_lines_array(int size)
{
	char	**lines;

	lines = (char **)malloc(sizeof(char *) * (size + 1));
	if (!lines)
		return (NULL);
	return (lines);
}

char	**read_all_lines(char *file, int fd)
{
	char	**lines;
	int		size;

	size = count_lines(fd);
	close(fd);
	if (size <= 0)
		return (NULL);
	lines = alloc_lines_array(size);
	if (!lines)
		return (NULL);
	fd = open(file, O_RDONLY);
	if (read_lines_into_array(lines, fd, size) == -1)
		return (NULL);
	return (lines);
}

int	is_invalid_tokens(char **tokens)
{
	if (!tokens || !tokens[0] || !tokens[1])
	{
		print_error("File doesn't contain identifiers", NULL);
		return (1);
	}
	if (tokens[2])
	{
		print_error(
			"Identifiers must contain: identifier and the path/color", NULL);
		return (1);
	}
	return (0);
}

int	is_valid_identifier(t_map *map, char *token)
{
	char	**tokens;
	int		result;

	tokens = ft_split(token, ' ');
	result = -1;
	if (is_invalid_tokens(tokens))
		return (free_array(&tokens), -1);
	if (!ft_strncmp(tokens[0], "NO", 3) || !ft_strncmp(tokens[0], "SO", 3)
		|| !ft_strncmp(tokens[0], "WE", 3) || !ft_strncmp(tokens[0], "EA", 3))
		result = handle_texture_identifier(map, tokens);
	else if (!ft_strncmp(tokens[0], "F", 2) || !ft_strncmp(tokens[0], "C", 2))
		result = handle_color_identifier(map, tokens);
	else
	{
		print_error("Unknown identifier type", NULL);
		result = -1;
	}
	free_array(&tokens);
	return (result);
}

int	parse_cub_file(char *file, t_map *map)
{
	int		fd;
	char	**file_content;
	int		i;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (print_error("Could not open file", NULL));
	file_content = read_all_lines(file, fd);
	if (!file_content || is_line_empty(file_content[0]))
		return (print_error("Empty file", NULL),
			free_lines(file_content), -1);
	if (parse_identifiers(file_content, map, &i) == -1)
		return (-1);
	if (get_map_info(file_content, &i, map) == -1)
		return (free_lines(file_content), -1);
	close(fd);
	return (free_lines(file_content), 0);
}
