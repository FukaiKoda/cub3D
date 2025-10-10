/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oayyoub <oayyoub@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 10:38:06 by habdella          #+#    #+#             */
/*   Updated: 2025/09/30 09:28:29 by oayyoub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Dcast.h"

char	*ft_strdupnl(char *contain)
{
	char	*line;
	int		i;
	int		j;

	if (!contain)
		return (NULL);
	i = 0;
	while (contain[i] && contain[i] != '\n')
		i++;
	line = ft_malloc(i + 1);
	j = 0;
	while (j < i)
	{
		line[j] = contain[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*update(char *contain)
{
	char	*p;
	int		i;

	i = 0;
	if (!contain)
		return (NULL);
	while (contain[i] && contain[i] != '\n')
		i++;
	if (contain[i])
		i++;
	p = ft_strdup(contain + i);
	return (p);
}

char	*get_container(char *contain, char *buff, int fd)
{
	ssize_t	reader;

	reader = read(fd, buff, BUFFER_SIZE);
	if (reader < 0 || !buff)
		return (NULL);
	while (reader > 0)
	{
		buff[reader] = '\0';
		if (!contain)
			contain = ft_strdup(buff);
		else if (buff)
		{
			contain = ft_strjoin(contain, buff);
		}
		if (ft_strchr(contain, '\n') || reader < BUFFER_SIZE)
			return (contain);
		reader = read(fd, buff, BUFFER_SIZE);
	}
	return (contain);
}

char	*get_next_line(t_game *game, int fd)
{
	static char	*contain = NULL;
	char		*buff;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || !game)
		return (contain = NULL, contain);
	buff = ft_malloc(BUFFER_SIZE + 1);
	contain = get_container(contain, buff, fd);
	if (!contain || !ft_strlen(contain))
		return (NULL);
	line = ft_strdupnl(contain);
	contain = update(contain);
	return (line);
}
