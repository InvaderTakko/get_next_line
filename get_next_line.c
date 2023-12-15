/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sruff <sruff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 17:49:40 by sruff             #+#    #+#             */
/*   Updated: 2023/12/15 17:58:08 by sruff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"

//#define BUFFER_SIZE 24
//void	search_destroy()
//char	*get_next_line(int fd)
//{
//	char 		*buffer;
//	static int	bytes_read;
//	int			temp_read;

//	buffer = NULL;
//	temp_read = 0;

//	while (temp_read < bytes_read && bytes_read)
//	{
//		//buffer = malloc(BUFFER_SIZE * sizeof(char) + 1);
//		read(fd, buffer, BUFFER_SIZE);
//		//buffer[BUFFER_SIZE] = '\0';
//		temp_read += BUFFER_SIZE;
//		//free(buffer);
//	}
//	//free(buffer);
//	buffer = malloc(BUFFER_SIZE * sizeof(char) + 1);
//	read(fd, buffer, BUFFER_SIZE);
//	buffer[BUFFER_SIZE] = '\0';
//	bytes_read += BUFFER_SIZE;
//	return (buffer);
//}
static char	*prepare_s(char *buffer, char *temp_buffer)
{
	char *cutter;
	char *temp_cutter;

	cutter = ft_strchr(buffer, '\n');
	temp_cutter = temp_buffer;
	if (cutter == NULL)
	{
		return (NULL);
	}
	if (*cutter)
	{
		cutter++;
		if (*cutter)
		{
			//free(buffer);
			buffer = ft_strdup(cutter);
			//temp_cutter = ft_strdup(temp_cutter);
			//temp_cutter++;
			//temp_cutter = ft_strchr(temp_buffer, '\n');
			//temp_cutter++;
			//*temp_cutter = '\0';
			//*buffer = '\0';
			
		}
		return(buffer);
	}
	return (NULL);
}

static char	*prepare(char *buffer, char *temp_buffer)
{
	char *cutter;
	char *temp_cutter;

	cutter = ft_strchr(buffer, '\n');
	temp_cutter = temp_buffer;
	if (cutter == NULL)
	{
		return (NULL);
	}
	if (*cutter)
	{
		cutter++;
		if (*cutter)
		{
			//free(buffer);
			temp_buffer = ft_strdup(buffer);
			buffer = ft_strdup(cutter);
			//temp_cutter = ft_strdup(temp_cutter);
			//temp_cutter++;
			temp_cutter = ft_strchr(temp_buffer, '\n');
			temp_cutter++;
			*temp_cutter = '\0';
			//*buffer = '\0';
			
		}
		return(temp_buffer);
	}
	return (NULL);
}

static char	*reading(int fd, char *buffer, char *temp_buffer)
{
	int		bytes;

	bytes = read(fd, temp_buffer, BUFFER_SIZE);
	temp_buffer[BUFFER_SIZE] = '\0'; 
	if (bytes == -1)
	{	
		free(buffer);
	 	free(temp_buffer);
		return (NULL);
	}
	//buffer = ft_strdup(temp_buffer);
	return (temp_buffer);
}

char *get_next_line(int fd)
{
    static char *buffer = NULL;
	char		*temp_buffer;
	char		*next_line;
    int 		bytes;

	bytes = 0;
	if (buffer)
	{
		bytes = ft_strlen(buffer);
	}
	temp_buffer = malloc(BUFFER_SIZE + bytes + 1);
	//strjoin
	temp_buffer = reading(fd, buffer, temp_buffer);
	if (buffer)
		buffer = ft_strjoin(buffer, temp_buffer);
	if (!buffer)	
		buffer = ft_strdup(temp_buffer);
	//if (temp_buffer== NULL)
	//	return (NULL);
	next_line = prepare(buffer, temp_buffer);
	if (!next_line)
		return (get_next_line(fd)); // split fn into static buf and next_line output
	buffer = prepare_s(buffer, temp_buffer);
	// strjoin()
	return (next_line);
}



int main(void)
{
    char *ptr = NULL;
    int file = open("example.txt", O_RDONLY);

    ptr = get_next_line(file);
	printf("%s", ptr);
	free(ptr);
	ptr = get_next_line(file);
	printf("%s", ptr);
	free(ptr);
	ptr = get_next_line(file);
	printf("%s", ptr);
	free(ptr);
	ptr = get_next_line(file);
	printf("%s", ptr);
	free(ptr);
    //while (1 == 1)
    //{
	//	ptr = get_next_line(file);
	//	if (ptr == NULL)
	//		break;
    //    printf("%s", ptr);
    //    //free(ptr);
    //}

    close(file);
    return 0;
}
