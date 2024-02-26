/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo-dolc <flo-dolc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 20:29:07 by flo-dolc          #+#    #+#             */
/*   Updated: 2024/02/26 20:29:08 by flo-dolc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_from_file(int fd, char *leftover)
{
	char		*buffer;
	char		*tmp;
	ssize_t		bytes_read;

	buffer = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!(ft_strchr(leftover, '\n')) && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		if (!leftover)
			leftover = ft_strdup("");
		tmp = leftover;
		leftover = ft_strjoin(tmp, buffer);
		free(tmp);
	}
	free(buffer);
	return (leftover);
}

char	*get_line(char *leftover)
{
	char	*line;
	int		len;

	len = 0;
	if (!leftover[len])
		return (NULL);
	while (leftover[len] && leftover[len] != '\n')
		len++;
	line = (char *) malloc(sizeof(char) * (len + 2));
	len = 0;
	while (leftover[len] && leftover[len] != '\n')
	{
		line[len] = leftover[len];
		len++;
	}
	if (leftover[len] == '\n')
		line[len] = leftover[len];
	else
		line[len] = '\0';
	line[len + 1] = '\0';
	return (line);
}

char	*get_new_leftover(char *leftover)
{
	char	*new_left;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (leftover[i] && leftover[i] != '\n')
		i++;
	if (!leftover[i])
	{
		free(leftover);
		return (NULL);
	}
	new_left = (char *) malloc(sizeof(char) * (ft_strlen(&leftover[i++]) + 1));
	while (leftover[i])
	{
		new_left[j] = leftover[i];
		j++;
		i++;
	}
	new_left[j] = '\0';
	free(leftover);
	return (new_left);
}

char	*get_next_line(int fd)
{
	static char	*leftover[4096];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	leftover[fd] = read_from_file(fd, leftover[fd]);
	if (!leftover[fd])
	{
		free(leftover[fd]);
		return (NULL);
	}
	line = get_line(leftover[fd]);
	leftover[fd] = get_new_leftover(leftover[fd]);
	return (line);
}
