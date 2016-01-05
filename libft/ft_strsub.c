/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschotte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 16:29:50 by jschotte          #+#    #+#             */
/*   Updated: 2016/01/04 16:33:54 by jschotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	unsigned int		i;
	unsigned int		j;
	unsigned int		k;
	char				*str;

	i = 0;
	k = 0;
	while (i != start)
		i++;
	if ((str = (char*)malloc(sizeof(char) * len + 1)) == NULL)
		return (NULL);
	if (i == start)
	{
		j = i;
		while (j < len + i)
		{
			str[k] = s[j];
			j++;
			k++;
		}
		str[k] = '\0';
		return (str);
	}
	return (str);
}
