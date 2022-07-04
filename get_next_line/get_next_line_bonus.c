/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurcia- <amurcia-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:17:31 by amurcia-          #+#    #+#             */
/*   Updated: 2022/06/07 14:56:51 by amurcia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>
// return 0 if EOF has been reached
// return -1 if an error happens
// return 1 if you read one line

char	*ft_cutword(char *ptr)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	while (ptr[i] != '\n' && ptr[i])
		i++;
	if (!ptr[i])
	{
		free(ptr);
		return (NULL);
	}
	if (ptr[i] == '\n')
		i++;
	dest = malloc(sizeof(char) * (ft_strlen(ptr) - i + 1));
	if (!dest)
		return (NULL);
	while (ptr[i])
		dest[j++] = ptr[i++];
	dest[j] = '\0';
	free(ptr);
	return (dest);
}

char	*ft_read(int fd, char *ptr)
{
	int		bytes;
	char	*temp;

	bytes = 1;
	temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (NULL);
	while (!ft_strchr(ptr, '\n') && bytes != 0)
	{
		bytes = read(fd, temp, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(temp);
			free(ptr);
			return (NULL);
		}
		temp[bytes] = '\0';
		ptr = ft_strjoin(ptr, temp);
	}
	free(temp);
	return (ptr);
}

char	*get_next_line(int fd)
{
	static char	*ptr[1024];
	char		*line;
	int			cont;

	cont = 0;
	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!ptr[fd])
		ptr[fd] = ft_strdup("");
	ptr[fd] = ft_read(fd, ptr[fd]);
	if (!ptr[fd])
	{
		free(ptr[fd]);
		return (NULL);
	}
	while (ptr[fd][cont] != '\n' && ptr[fd][cont])
		cont++;
	line = ft_substr(ptr[fd], 0, cont + 1);
	ptr[fd] = ft_cutword(ptr[fd]);
	if (!line || !line[0])
	{
		free(line);
		return (NULL);
	}
	return (line);
}
