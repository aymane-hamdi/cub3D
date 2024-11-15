/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 08:56:03 by akheired          #+#    #+#             */
/*   Updated: 2024/11/03 10:40:49 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_line(char **tmp_map, char *line)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (line[++i])
		if (line[i] == ',')
			j++;
	if (j != 2)
		return (1);
	i = 0;
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'
		|| line[i] == ',' || (line[i] >= '0' && line[i] <= '9'))
		i++;
	if (line[i] != '\0')
		return (1);
	if (line_len(tmp_map) != 3)
		return (1);
	return (0);
}

int	check_map_row_start(char *map_line)
{
	int	i;

	i = 0;
	while (map_line[i] == ' ' || map_line[i] == '\t')
		i++;
	if (map_line[i] == '0' || map_line[i] == '1')
		return (1);
	return (0);
}

void	check_space(t_config *config, int i, int j)
{
	if (i == 0 || j == 0 || i == config->map->map_height - 1
		|| j == row(config->map->map_buffer[i]) - 1
		|| (config->map->map_buffer[i + 1] && 
			config->map->map_buffer[i + 1][j] == ' ')
		|| (config->map->map_buffer[i - 1]
			&& config->map->map_buffer[i - 1][j] == ' ')
		|| config->map->map_buffer[i][j + 1] == ' '
		|| config->map->map_buffer[i][j - 1] == ' ')
	{
		printf("Error\nInvalide Map!\n");
		exit(1);
	}
}

void	check_player(t_config *config)
{
	int	i;
	int	j;

	i = -1;
	while (config->map->map_buffer[++i])
	{
		j = -1;
		while (config->map->map_buffer[i][++j])
		{
			if (config->map->map_buffer[i][j] == 'N' 
					|| config->map->map_buffer[i][j] == 'E'
				|| config->map->map_buffer[i][j] == 'S' 
				|| config->map->map_buffer[i][j] == 'W')
			{
				config->player_direction = config->map->map_buffer[i][j];
				config->player.x = j * config->size;
				config->player.y = i * config->size;
				config->p_d_count++;
				determine_engle(&config, i, j);
			}
		}
	}
	config->map->map_height = i;
	if (config->p_d_count != 1)
		errr();
}

void	check_map(t_config *config)
{
	int	i;

	i = -1;
	while (config->map->map_buffer[++i])
	{
		if (skip_line(config->map->map_buffer[i]))
		{
			printf("Error\nEmpty Line\n");
			exit(1);
		}
		if (check_chars(config->map->map_buffer[i]))
		{
			printf("Error\nCheck Characters\n");
			exit(1);
		}
	}
}
