/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:00:30 by ahamdi            #+#    #+#             */
/*   Updated: 2024/09/27 11:25:40 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	chke_ori(t_config **data, int i)
{
	int	map_y;
	int	map_x;

	map_y = (int)((*data)->rays[i].horiz_y / TILE_SIZE);
	map_x = (int)((*data)->rays[i].horiz_x / TILE_SIZE);
	if ((*data)->rays[i].distance <= 50
		&& map_y >= 0 && map_y < (*data)->map->map_height
		&& (*data)->map->map_buffer[map_y]
		&& map_x >= 0 && map_x < (*data)->map->map_width
		&& ((*data)->map->map_buffer[map_y][map_x] == 'D'
		|| (*data)->map->map_buffer[map_y][map_x] == '4'))
	{
		(*data)->dor_x = map_x;
		(*data)->dor_y = map_y;
		return (1);
	}
	return (0);
}

int	chek_ver(t_config **data, int i)
{
	int	map_y;
	int	map_x;

	map_y = (int)((*data)->rays[i].vert_y / TILE_SIZE);
	map_x = (int)((*data)->rays[i].vert_x / TILE_SIZE);
	if ((*data)->rays[i].distance <= 50
		&& map_y >= 0 && map_y < (*data)->map->map_height
		&& (*data)->map->map_buffer[map_y]
		&& map_x >= 0 && map_x < (*data)->map->map_width
		&& ((*data)->map->map_buffer[map_y][map_x] == 'D'
		|| (*data)->map->map_buffer[map_y][map_x] == '4'))
	{
		(*data)->dor_x = map_x;
		(*data)->dor_y = map_y;
		return (1);
	}
	return (0);
}

void	chek_door(t_config **data)
{
	int	i;

	i = 0;
	(*data)->dor_x = -1;
	(*data)->dor_y = -1;
	while (i < (*data)->width_window)
	{
		if ((*data)->rays[i].flag == 1)
		{
			if (chke_ori(data, i) == 1)
				return ;
		}
		else
		{
			if (chek_ver(data, i) == 1)
				return ;
		}
		i++;
	}
}
