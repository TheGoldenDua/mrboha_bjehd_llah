/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-ganb <del-ganb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:32:46 by del-ganb          #+#    #+#             */
/*   Updated: 2025/05/19 12:32:47 by del-ganb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	res;
	int	signe;

	i = 0;
	signe = 1;
	res = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			signe *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + (nptr[i] - '0');
		i++;
	}
	return (res * signe);
}

char	*ft_strdup(const char *s)
{
	char	*tmp;
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	tmp = (char *)malloc((len + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	while (s[i])
	{
		tmp[i] = s[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (!n)
		return (0);
	while (i < n - 1 && str1[i] && str2[i] && str1[i] == str2[i])
	{
		i++;
	}
	if (i == n)
		return (0);
	return (str1[i] - str2[i]);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*res;

	if (s1 == 0 || set == 0)
		return (NULL);
	start = 0;
	while (s1[start] && is_set(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && is_set(set, s1[end - 1]))
		end--;
	res = (char *)malloc((end - start + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (i + start < end)
	{
		res[i] = ((char *)s1)[i + start];
		i++;
	}
	res[i] = '\0';
	return (res);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (!dstsize)
		return (0);
	i = 0;
	while (i < dstsize - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (i);
}
