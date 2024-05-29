/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrahins <lbrahins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:52:25 by lbrahins          #+#    #+#             */
/*   Updated: 2024/05/29 11:23:34 by lbrahins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
		return (NULL);
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
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[0])
		return (NULL);
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
	char	buffer[BUFFER_SIZE + 1];
	int		bytesread;

	bytesread = 1;
	while (!search_newline(stash) && bytesread > 0)
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread == -1)
			return (NULL);
		buffer[bytesread] = '\0';
		stash = ft_strjoin(stash, buffer);
		if (!stash)
			return (NULL);
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	line = NULL;
	stash = fd_reader(fd, stash);
	if (!stash)
		return (free(stash), NULL);
	line = get_line(stash);
	if (!line)
		return (free(stash), free(line), NULL);
	stash = get_restover(stash);
	if (!stash)
		return(free(stash), NULL);
	return (line);
}
// #include <fcntl.h>
// #include <stdio.h>

// int	main()
// {	
// 	int fd = open("empty.txt", O_RDONLY);
// 	char	*test = get_next_line(fd);
// 	printf("%s", test);
// 	close(fd);
// 	free(test);
// 	return (0);
// }
