/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 09:00:19 by akheired          #+#    #+#             */
/*   Updated: 2024/10/18 12:19:13 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	skip_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (!line[i] || line[i] == '\n')
		return (1);
	return (0);
}

void	free_line(char **line)
{
	int	i;

	i = -1;
	while (line[++i])
		free(line[i]);
	free(line);
}

int	line_len(char **line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	return (i);
}

void	set_directions(char **identifier, char *line)
{
	if (*identifier != NULL)
	{
		printf("Error\nDuplicated Path Directions\n");
		exit(1);
	}
	*identifier = ft_strdup(line);
}

int	check_chars(char *line)
{
	int	i;

	i = -1;
	while (line[++i] != ' ' && line[i] != '\n' && line[i] != '0'
		&& line[i] != '1' && line[i] != 'W' && line[i] != 'D'
		&& line[i] != 'N' && line[i] != 'S')
		return (1);
	return (0);
}
