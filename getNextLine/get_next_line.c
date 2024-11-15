/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 12:37:45 by ahamdi            #+#    #+#             */
/*   Updated: 2024/09/22 18:15:35 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_chekfree(char *str, char *buff)
{
	free(buff);
	free(str);
}

char	*ft_read(int fd, char *str, int r_byt)
{
	char	*buff;
	char	*temp;

	buff = malloc((BUFFER_SIZE + 1));
	if (!buff)
	{
		free(str);
		return (NULL);
	}
	while (r_byt != 0 && !ft_strchr(str, '\n'))
	{
		r_byt = read(fd, buff, BUFFER_SIZE);
		if (r_byt == -1)
		{
			ft_chekfree(str, buff);
			return (NULL);
		}
		buff[r_byt] = '\0';
		temp = str;
		str = ft_strjoin(str, buff);
		free(temp);
	}
	free(buff);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;
	size_t		i;
	int			r_byt;

	r_byt = 1;
	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0) 
		return (NULL);
	str = ft_read(fd, str, r_byt);
	if (!str)
		return (NULL);
	line = ft_premierstr(str, i);
	if (!line)
	{
		free(str);
		str = NULL;
		return (NULL);
	}
	str = ft_desiemstr(str, i);
	return (line);
}
