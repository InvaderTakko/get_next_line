/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 17:49:40 by sruff             #+#    #+#             */
/*   Updated: 2024/01/06 19:26:51 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	multi_free(char **ptr1, char **ptr2, char	**ptr3)
{
	if (ptr1)
	{
		free(*ptr1);
		*ptr1 = NULL;
	}
	if (ptr2)
	{
		free(*ptr2);
		*ptr2 = NULL;
	}
	if (ptr3)
	{
		free(*ptr3);
		*ptr3 = NULL;
	}
}

static void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const char	*s;
	char		*d;

	s = (char *)src;
	d = (char *)dst;
	if (!d && !s)
		return (NULL);
	if (d < s)
	{
		while (len--)
			*d++ = *s++;
	}
	else if (d > s)
	{
		d = d + len - 1;
		s = s + len - 1;
		while (len--)
			*d-- = *s--;
	}
	return (dst);
}

static void	prep_nl(char *buffer, t_gnl *gnl)
{
	char	*nl_ptr;
	char	*substr;

	nl_ptr = ft_strchr(buffer, '\n');
	if (nl_ptr)
	{
		nl_ptr++;
		substr = ft_substr(buffer, 0, nl_ptr - buffer);
		gnl->temp = ft_strjoin(gnl->next_line, substr);
		multi_free(&gnl->next_line, &substr, NULL);
		gnl->next_line = gnl->temp;
		ft_memmove(buffer, nl_ptr, ft_strlen(nl_ptr) + 1);
	}
	if (!nl_ptr)
	{
		gnl->temp = ft_strjoin(gnl->next_line, buffer);
		multi_free(&gnl->next_line, NULL, NULL);
		gnl->next_line = gnl->temp;
		buffer[0] = '\0';
	}
}

static char	*read_nl(char *buffer, t_gnl *gnl)
{
	while (!ft_strchr(buffer, '\n') && !(gnl->bytes < BUFFER_SIZE))
	{
		gnl->temp = ft_strjoin(gnl->next_line, buffer);
		multi_free(&gnl->next_line, NULL, NULL);
		gnl->next_line = gnl->temp;
		gnl->bytes = read(gnl->fd, buffer, BUFFER_SIZE);
		if (gnl->bytes == -1)
		{
			buffer[0] = '\0';
			gnl->temp = NULL;
			return (multi_free(&gnl->next_line, NULL, NULL), NULL);
		}
	}
	buffer[gnl->bytes] = '\0';
	gnl->temp = NULL;
	return ("1");
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	t_gnl		gnl;

	gnl.fd = fd;
	gnl.next_line = NULL;
	gnl.bytes = BUFFER_SIZE;
	gnl.temp = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!read_nl(buffer, &gnl))
		return (NULL);
	prep_nl(buffer, &gnl);
	return (gnl.next_line);
}
//int main(void)
//{
//    char *ptr = NULL;
//    int file = open("example.txt", O_RDONLY);

//	// BUFFER_SIZE 5 doesnt work check prepare
//    ptr = get_next_line(file);
//	printf("%s", ptr);
//	free(ptr);
//	ptr = get_next_line(file);
//	printf("%s", ptr);
//	free(ptr);
//	ptr = get_next_line(file);
//	printf("%s", ptr);
//	free(ptr);
//	ptr = get_next_line(file);
//	printf("%s", ptr);
//	free(ptr);
//	ptr = get_next_line(file);
//	printf("%s", ptr);
//	free(ptr);
//	ptr = get_next_line(file);
//	printf("%s", ptr);
//	free(ptr);
//	ptr = get_next_line(file);
//	printf("%s", ptr);
//	free(ptr);
//	ptr = get_next_line(file);
//	printf("%s", ptr);
//	free(ptr);
//	ptr = get_next_line(file);
//	printf("%s", ptr);
//	free(ptr);
//    //while (1 == 1)
//    //{
//	//	ptr = get_next_line(file);
//	//	if (ptr == NULL)
//	//		break;
//    //    printf("%s", ptr);
//    //    //free(ptr);
//    //}

//    close(file);
//    return 0;
//}