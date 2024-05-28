/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrahins <lbrahins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:52:25 by lbrahins          #+#    #+#             */
/*   Updated: 2024/05/28 14:07:56 by lbrahins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*stash_realloc(char *old, char *buffer)
{
	size_t	i;
	char	*new;

	i = 0;
	new = NULL;
	new = malloc(sizeof(char) * (ft_strlen(old) + ft_strlen(buffer) + 1));
	if (!new)
		return (NULL);
	while (*old)
	{
		new[i++] = *old;
		old++;
	}
	free(old);
	while (*buffer)
	{
		new[i++] = *buffer;
		buffer++;
	}
	new[i] = '\0';
	return (new);
}

static void	fd_reader(int fd, char *stash, int *bytesread)
{
	char	*buffer;

	while (!search_newline(stash) && *bytesread > 0)
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return ;
		*bytesread = read(fd, buffer, BUFFER_SIZE);
		if (*bytesread <= 0)
		{
			free(buffer);
			return ;
		}
		buffer[BUFFER_SIZE] = '\0';
		stash_realloc(stash, buffer);
		free(buffer);
	}
}

static char	*get_line(char *stash)
{
	char	*line;
	int		end_i;
	int		i;

	i = 0;
	end_i = search_newline(stash);
	line = malloc(sizeof(char) * (end_i));
	if (!line)
		return (NULL);
	while (i != end_i)
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*stash_cleanup(char *stash)
{
	int		i;
	int		end_i;
	char	*new;

	i = 0;
	end_i = search_newline(stash) + 1;
	new = malloc(sizeof(char) * (ft_strlen(&stash[end_i]) + 1));
	if (!new)
		return (NULL);
	while (new[i])
		new[i++] = stash[end_i++];
	new[i] = '\0';
	free(stash);
	return (new);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash;
	int			bytesread;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) <= 0)
		return (NULL);
	bytesread = 1;
	line = NULL;
	if (!stash)
		stash = "";
	fd_reader(fd, stash, &bytesread);
	line = get_line(stash);
	if (!line[0])
	{
		free(stash);
		return (NULL);
	}
	stash = stash_cleanup(stash);
	return (line);
}
