/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrahins <lbrahins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:52:25 by lbrahins          #+#    #+#             */
/*   Updated: 2024/05/28 14:57:35 by lbrahins         ###   ########.fr       */
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
	if (old)
	{
		while (*old)
		{
			new[i++] = *old;
			old++;
		}
		free(old);
	}
	
	while (*buffer)
	{
		new[i++] = *buffer;
		buffer++;
	}
	new[i] = '\0';
	return (new);
}

static void	fd_reader(int fd, char *stash)
{
	char	buffer[BUFFER_SIZE + 1];
	int		bytesread;

	bytesread = 1;
	while (!search_newline(stash) && bytesread > 0)
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread <= 0)
			return ;
		buffer[BUFFER_SIZE] = '\0';
		stash = stash_realloc(stash, buffer);
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

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	line = NULL;
	fd_reader(fd, stash);
	if (!stash)
		return (NULL);
	line = get_line(stash);
	if (!line)
	{
		free(stash);
		free(line);
		return (NULL);
	}
	stash = stash_cleanup(stash);
	return (line);
}
// #include <fcntl.h>
// #include <stdio.h>

// int	main()
// {	
// 	int fd = open("1char.txt", O_RDONLY);
// 	printf("%s", get_next_line(fd));
// 	return (0);
// }
