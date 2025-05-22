/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aourhou <aourhou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:32:28 by del-ganb          #+#    #+#             */
/*   Updated: 2025/05/22 17:03:09 by aourhou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	handle_color_identifier(t_map *map, char **tokens)
{
	if (!ft_strncmp(tokens[0], "F", 2))
	{
		if (map->floor_clr != -1)
		{
			print_error("Floor color defined more than once", NULL);
			return (-1);
		}
		return (set_color(&map->floor_clr, tokens[1]));
	}
	if (!ft_strncmp(tokens[0], "C", 2))
	{
		if (map->ceiling_clr != -1)
		{
			print_error("Ceiling color defined more than once", NULL);
			return (-1);
		}
		return (set_color(&map->ceiling_clr, tokens[1]));
	}
	return (-1);
}

static int	count_commas(char *str)
{
	int		i;
	int		count;
	int		space_count;
	char	*tmp;

	i = 0;
	count = 0;
	space_count = 0;
	tmp = ft_strtrim(str, " \t");
	while (tmp[i])
	{
		if (tmp[i] == ',')
			count++;
		if (tmp[i] == ' ' || tmp[i] == '\t')
			space_count++;
		i++;
	}
	free(tmp);
	if (count > 2 || space_count >= 1)
		return (-1);
	return (0);
}

int	set_color(int *color_field, char *value)
{
	int		r;
	int		g;
	int		b;
	char	**color;

	if (*color_field != -1)
		return (print_error("Color defined more than once", NULL), -1);
	if (count_commas(value) == -1)
	{
		printf("Invalid color format\n");
		return (-1);
	}
	color = ft_split(value, ',');
	if (validate_rgb_values(color, 2) == -1)
		return (-1);
	r = ft_atoi(color[0]);
	g = ft_atoi(color[1]);
	b = ft_atoi(color[2]);
	*color_field = (r << 16) | (g << 8) | b;
	free_split(color);
	return (0);
}
