/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:54:45 by sruff             #+#    #+#             */
/*   Updated: 2023/12/15 12:19:02 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (*str)
	{
		if (*str == (char)c)
			return (str);
		str++;
	}
	if ((char)c == '\0')
		return (str);
	return (NULL);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize != 0)
	{
		while (*(src + i) && i < dstsize - 1)
		{
			*(dst + i) = *(src + i);
			i++;
		}
		*(dst + i) = '\0';
	}
	while (*(src + i))
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*ptr;

	len = sizeof(char) * ft_strlen(s1) + 1;
	ptr = malloc(len);
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s1, len);
	return (ptr);
}

size_t	ft_strlen(const char *s)
{
	int	l;

	l = 0;
	while (s[l] != '\0')
		l++;
	return (l);
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	sumlen;
	char	*smalloc;

	if (!s1 && !s2)
		return (NULL);
	sumlen = (ft_strlen(s1) + ft_strlen(s2) + 1);
	smalloc = malloc(sumlen * sizeof(char));
	if (!smalloc)
		return (NULL);
	ft_strlcpy(smalloc, s1, ft_strlen(s1) +1);
	ft_strlcpy(&smalloc[ft_strlen(s1)], s2, ft_strlen(s2) + 1);
	return (smalloc);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	char			*subm;
	size_t			slen;

	sub = (char *)s;
	if (!s)
		return (0);
	slen = ft_strlen(s);
	if (start >= slen || (start == 0 && len == 0))
		return (ft_strdup(""));
	if (slen - start < len)
		len = slen - start;
	subm = malloc((len + 1) * sizeof(char));
	if (!subm)
		return (NULL);
	ft_strlcpy(subm, sub + start, len + 1);
	return (subm);
}