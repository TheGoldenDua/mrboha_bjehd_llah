/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-ganb <del-ganb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 09:44:45 by del-ganb          #+#    #+#             */
/*   Updated: 2025/03/17 16:12:24 by del-ganb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_line(char *str)
{
	int	i;

	i = 0;
	if (!*str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	return (ft_substr(str, 0, i + 1));
}

static char	*free_buffer(char *str)
{
	int		i;
	char	*res;

	i = 0;
	if (!*str)
	{
		free(str);
		return (NULL);
	}
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	res = ft_dup(&str[i]);
	free(str);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*stash;
	char		*my_line;
	ssize_t		end;

	end = 1;
	if (fd < 0 || fd > MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	stash = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!stash)
		return (NULL);
	stash[0] = 0;
	while (end > 0 && !ft_strchr(stash, '\n'))
	{
		end = read(fd, stash, BUFFER_SIZE);
		if (end < 0)
			return (free(stash), free(buffer), NULL);
		stash[end] = '\0';
		buffer = ft_strjoin(buffer, stash);
	}
	my_line = get_line(buffer);
	buffer = free_buffer(buffer);
	free(stash);
	return (my_line);
}
