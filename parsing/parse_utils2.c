/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-ganb <del-ganb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:32:54 by del-ganb          #+#    #+#             */
/*   Updated: 2025/05/19 12:32:55 by del-ganb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_map_line(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (*line == '1' || *line == '0');
}

int	print_error(char *msg, t_map *map)
{
	printf("Error\n%s\n", msg);
	free_data(map);
	return (-1);
}

int	is_set(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	remove_new_line(char *line)
{
	int	len;

	if (!line)
		return ;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
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
