/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/28 09:30:10 by jschotte          #+#    #+#             */
/*   Updated: 2016/01/04 16:28:35 by jschotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static int	get_line(int const fd, char *buffer, char *save[fd], int *end)
{
	int		ret;
	char	*c;
	char	*tmp;

	while ((c = ft_strchr(save[fd], '\n')) == NULL &&
			(ret = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		tmp = save[fd];
		save[fd] = ft_strjoin(tmp, buffer);
		ft_strdel(&tmp);
	}
	if (buffer == NULL && ret == 0)
		*end = 1;
	ft_strdel(&buffer);
	if (ret == -1)
		return (-1);
	if (!c && ret == 0)
		return (0);
	return (1);
}

static int	get_endfile(int *end, char **save, char **buffer, char **line)
{
	if (ft_strlen(*buffer) != 0 && *end == 0)
	{
		*line = ft_strdup(*buffer);
		*save = NULL;
		*end = 1;
		return (1);
	}
	*line = *save;
	*save = NULL;
	return (0);
}

int			get_next_line(int const fd, char **line)
{
	static char	*save[MAX_FD];
	char		*buffer;
	int			ret;
	static int	end = 0;
	char		*tmp;

	buffer = ft_strnew(BUFF_SIZE);
	if (fd < 0 || line == NULL || buffer == NULL || BUFF_SIZE < 1)
		return (-1);
	if (save[fd] == NULL)
		save[fd] = ft_strnew(1);
	ret = get_line(fd, buffer, save, &end);
	if (ret == -1)
		return (-1);
	if (ret == 0)
	{
		return (get_endfile(&end, &save[fd], &buffer, line));
	}
	*line = ft_strsub(save[fd], 0, ft_strchr(save[fd], '\n') - save[fd]);
	tmp = save[fd];
	save[fd] = ft_strdup(ft_strchr(save[fd], '\n') + 1);
	ft_strdel(&tmp);
	return (1);
}
