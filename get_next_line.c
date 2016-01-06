/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/28 09:30:10 by jschotte          #+#    #+#             */
/*   Updated: 2016/01/06 13:23:54 by jschotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	get_line(int const fd, char *buffer, char *save[fd])
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
	ft_strdel(&buffer);
	if (ret == -1)
		return (-1);
	if (!c && ret == 0)
		return (0);
	return (1);
}

int			get_next_line(int const fd, char **line)
{
	static char	*save[MAX_FD];
	char		*buffer;
	int			ret;
	char		*str;
	char		*tmp;

	buffer = ft_strnew(BUFF_SIZE);
	if (fd < 0 || line == NULL || buffer == NULL || BUFF_SIZE < 1)
		return (-1);
	if (save[fd] == NULL)
		save[fd] = ft_strnew(1);
	ret = get_line(fd, buffer, save);
	if (ret == -1)
		return (-1);
	if ((str = ft_strchr(save[fd], '\n')) != NULL)
	{
		*line = ft_strsub(save[fd], 0, str - save[fd]);
		tmp = save[fd];
		save[fd] = ft_strdup(str + 1);
		ft_strdel(&tmp);
		return (1);
	}
	while ((ret = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		tmp = save[fd];
		save[fd] = ft_strjoin(tmp, buffer);
		ft_strdel(&tmp);
	}
	*line = ft_strdup(save[fd]);
	save[fd] = NULL;
	if (ft_strlen(*line) > 0)
		return (1);
	return (0);
}
