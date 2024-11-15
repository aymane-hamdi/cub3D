/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 08:48:04 by akheired          #+#    #+#             */
/*   Updated: 2024/11/03 10:42:15 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	*init_color(char **line)
{
	int	*colors;
	int	nb;
	int	i;
	int	j;

	colors = ft_calloc(3, sizeof(int));
	if (!colors)
		return (NULL);
	i = 0;
	while (line[i] && i < 3)
	{
		nb = 0;
		j = 0;
		while (line[i][j] == ' ' || line[i][j] == '\t')
			j++;
		while (line[i][j] >= '0' && line[i][j] <= '9')
		{
			nb = nb * 10 + (line[i][j] - '0');
			j++;
		}
		colors[i] = nb;
		i++;
	}
	return (colors);
}

void	init_fc(t_config *config, char *line, int i, char *fc_config)
{
	int		j;
	char	**tmp_map;

	j = 0;
	while (config->maps[i][j] == ' ' || config->maps[i][j] == '\t'
		|| config->maps[i][j] == 'F' || config->maps[i][j] == 'C')
		j++;
	tmp_map = ft_split(line + j, ',');
	if (check_line(tmp_map, line + j))
	{
		printf("Error\nCheck lines\n"); 
		exit(1);
	}
	if (fc_config[0] == 'F' && !config->map->floor_color)
		config->map->floor_color = init_color(tmp_map);
	else if (fc_config[0] == 'C' && !config->map->ceiling_color)
		config->map->ceiling_color = init_color(tmp_map);
	else if (config->map->floor_color || config->map->ceiling_color)
	{
		printf("Error\nDuplicated F || C\n"); 
		exit(1);
	}
	free_line(tmp_map);
}

void	errr(void)
{
	printf("Error\nNo more one player\n");
	exit(1);
}
