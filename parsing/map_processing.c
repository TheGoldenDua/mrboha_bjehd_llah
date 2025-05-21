/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_processing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aourhou <aourhou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:32:19 by del-ganb          #+#    #+#             */
/*   Updated: 2025/05/20 13:13:40 by aourhou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	count_lines(int fd)
{
	char	*line;
	int		count;

	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		remove_new_line(line);
		free(line);
		count++;
		line = get_next_line(fd);
	}
	if (count == 0)
		return (-1);
	return (count);
}

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W');
}

void	free_data(t_map *map)
{
	if (!map)
		return ;
	free_wall(&map->n_wall);
	free_wall(&map->s_wall);
	free_wall(&map->w_wall);
	free_wall(&map->e_wall);
	free_map_grid(&map->map_grid);
}

int	get_max_width(char **map)
{
	int	i;
	int	current_len;
	int	max_len;

	i = 0;
	current_len = 0;
	max_len = 0;
	while (map[i])
	{
		current_len = ft_strlen(map[i]);
		if (current_len > max_len)
			max_len = current_len;
		i++;
	}
	return (max_len);
}

char	*fill_line_spaces(const char *line, int max_width)
{
	int		i;
	char	*padded_line;

	padded_line = malloc(sizeof(char) * (max_width + 1));
	if (!padded_line)
		return (NULL);
	i = 0;
	while (line[i])
	{
		padded_line[i] = line[i];
		i++;
	}
	while (i < max_width)
	{
		padded_line[i] = ' ';
		i++;
	}
	padded_line[i] = '\0';
	return (padded_line);
}
