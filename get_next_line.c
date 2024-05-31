/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrahins <lbrahins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:52:25 by lbrahins          #+#    #+#             */
/*   Updated: 2024/05/31 14:08:23 by lbrahins         ###   ########.fr       */
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
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	line = NULL;
	stash = fd_reader(fd, stash);
	if (!stash)
		return (NULL);
	line = get_line(stash);
	stash = get_restover(stash);
	return (line);
}
// int	main()
// {	
// 	int fd = open("read_error.txt", O_RDONLY);
// 	char	*test = get_next_line(fd);
// 	char	*expect = "aaaaaaaaaa\n";
// 	// 1
// 	printf("result: \t%ld, %s", ft_strlen(test), test);
// 	printf("expected: \t%ld, %s", ft_strlen(expect), expect);
	
// 	test = get_next_line(fd);
// 	expect = "bbbbbbbbbb\n";
// 	// 2
// 	printf("result: \t%ld, %s", ft_strlen(test), test);
// 	printf("expected: \t%ld, %s", ft_strlen(expect), expect);
	
// 	test = get_next_line(fd);
// 	expect = "bbbbbbbbbb\n";
// 	// 3
// 	printf("result: \t%ld, %s", ft_strlen(test), test);
// 	printf("expected: \t%ld, %s", ft_strlen(expect), expect);
	
// 	test = get_next_line(fd);
// 	test = get_next_line(fd);
// 	expect = NULL;
// 	// 4
// 	printf("result: \t%ld, %s\n", ft_strlen(test), test);
// 	printf("expected: \t%ld, %s\n", ft_strlen(expect), expect);

// 	close(fd);
// 	fd = open("read_error.txt", O_RDONLY);
// 	test = get_next_line(fd);
// 	expect = "aaaaaaaaaa\n";
// 	// 5
// 	printf("result: \t%ld, %s", ft_strlen(test), test);
// 	printf("expected: \t%ld, %s", ft_strlen(expect), expect);
	
// 	close(fd);
// 	free(test);
// 	return (0);
// }
