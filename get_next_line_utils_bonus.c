/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrahins <lbrahins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:52:22 by lbrahins          #+#    #+#             */
/*   Updated: 2024/06/07 16:13:34 by lbrahins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	search_newline(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *old, char *buffer)
{
	int		i;
	int		j;
	char	*new;

	if (!old)
	{
		old = malloc(sizeof(char) * 1);
		if (!old)
			return (NULL);
		old[0] = '\0';
	}
	if (!buffer)
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlen(old) + ft_strlen(buffer) + 1));
	if (!new)
		return (free(old), NULL);
	i = -1;
	j = 0;
	while (old[++i])
		new[i] = old[i];
	while (buffer[j])
		new[i++] = buffer[j++];
	new[i] = '\0';
	return (free(old), new);
}
