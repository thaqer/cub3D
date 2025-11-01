/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaniatt <tbaniatt@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 09:18:18 by tbaniatt          #+#    #+#             */
/*   Updated: 2024/09/18 19:53:56 by tbaniatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	l1;
	size_t	l2;
	char	*str;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (l1 + l2 + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < l1)
	{
		str[i] = s1[i];
		i++;
	}
	while (i < l1 + l2)
	{
		str[i] = s2[i - l1];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	x;
	size_t	s_len;
	char	*str;

	x = 0;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > (s_len - start))
		len = s_len - start;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (s[start + x] && x < len)
	{
		str[x] = s[start + x];
		x++;
	}
	str[x] = '\0';
	return (str);
}

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		x;
	int		len;

	x = 0;
	len = ft_strlen(s);
	dest = (char *)malloc(len * sizeof(char) + 1);
	if (!dest)
		return (NULL);
	while (s[x])
	{
		dest[x] = s[x];
		x++;
	}
	dest[x] = '\0';
	return (dest);
}

size_t	ft_strlen(const char *s)
{
	size_t	x;

	x = 0;
	while (s[x] != '\0')
		x++;
	return (x);
}
