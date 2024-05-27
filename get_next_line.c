/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrahins <lbrahins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:52:25 by lbrahins          #+#    #+#             */
/*   Updated: 2024/05/27 15:46:57 by lbrahins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*stash_realloc(char *old, char *buf)
{
	char	*new_buffer;
	size_t	old_len;
	size_t	buf_len;
	size_t	i;

	i = 0;
	old_len = ft_strlen(old);
	buf_len = ft_strlen(buf);
	new_buffer = malloc((old_len + buf_len) + 1);
	if (!new_buffer)
		return (NULL);
	while (*old)
	{
		new_buffer[i++] = *old;
		old++;
	}
	free(old);
	while (*buf)
	{
		new_buffer[i++] = *buf;
		buf++;
	}
	new_buffer[i] = '\0';
	return (new_buffer);
}

static int	stash_cleanup(char *old, size_t end_i)
{
	char	*new;

	new = ft_strdup(&old[end_i]);
	free (old);
	if (!new)
		return (1);
	return (0);
}

static char	*line_cutter(char *stash)
{
	size_t	end_i;
	char	*line;

	end_i = ft_strchr_i(stash, '\0');
	line = malloc((end_i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	line = ft_strncpy(line, stash, end_i);
	stash_cleanup(stash, end_i);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char	buffer[BUFFER_SIZE + 1];
	char	line;
	int		bytesread;

	if (!fd)
		return (NULL);
	bytesread = read(fd, buffer, BUFFER_SIZE);
	while (bytesread > 0)
	{
		buffer[bytesread] = '\0';
		stash = stash_realloc(stash, buffer);
		if (!stash)
			return (NULL);
		if (ft_strchr_i(stash, '\0'))
		{
			line = line_cutter(stash);
			return (stash_cleanup(stash, ft_strchr_i(stash, '\0')), line);
		}
		bytesread = read(fd, buffer, BUFFER_SIZE);
	}
	free(stash);
	return (NULL);
}
