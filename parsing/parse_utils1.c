#include "../includes/cub3d.h"

int	ft_isdigit(int c)
{
	return (c <= '9' && c >= '0');
}

int	ft_count_word(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] == c)
	{
		i++;
	}
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || !s[i + 1]))
			count++;
		i++;
	}
	return (count);
}

char	*ft_fill_word(char const *s, char c)
{
	size_t	len;
	size_t	i;
	char	*str;

	len = 0;
	i = 0;
	while (s[len] && s[len] != c)
		len++;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (s[i] && i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	*free_split(char **str, size_t *j)
{
	size_t	k;

	k = 0;
	while (k < *j)
	{
		free(str[k]);
		k++;
	}
	free(str);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	j;

	if (!s)
		return (NULL);
	j = 0;
	split = (char **)malloc(sizeof(char *) * (ft_count_word(s, c) + 1));
	if (split == NULL)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (!*s)
			break ;
		split[j] = ft_fill_word(s, c);
		if (!split[j])
			return (free_split(split, &j));
		s += ft_strlen(split[j++]);
	}
	split[j] = 0;
	return (split);
}