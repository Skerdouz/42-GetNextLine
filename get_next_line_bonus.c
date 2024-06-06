/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrahins <lbrahins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:52:25 by lbrahins          #+#    #+#             */
/*   Updated: 2024/06/06 17:26:53 by lbrahins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*get_restover(char *old)
{
	char	*new;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (old[i] && old[i] != '\n')
		i++;
	if (!old[i])
		return (free(old), NULL);
	new = malloc(sizeof(char) * ((ft_strlen(old) - i) + 1));
	if (!new)
		return (NULL);
	i++;
	while (old[i])
		new[j++] = old[i++];
	new[j] = '\0';
	return (free(old), new);
}

static char	*get_line(char *stash)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!stash[0])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*fd_reader(int fd, char *stash)
{
	char	*buffer;
	int		bytesread;

	bytesread = 1;
	if (!stash)
		stash = NULL;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (!search_newline(stash) && bytesread > 0)
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread == -1)
			return (free(buffer), NULL);
		buffer[bytesread] = '\0';
		stash = ft_strjoin(stash, buffer);
	}
	return (free(buffer), stash);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash[1024];

	if (fd < 0 || fd > 1023 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
	{
		if (stash[fd])
			free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	line = NULL;
	stash[fd] = fd_reader(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = get_line(stash[fd]);
	stash[fd] = get_restover(stash[fd]);
	return (line);
}
