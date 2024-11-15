/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chek_distance_horizental.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:37:07 by ahamdi            #+#    #+#             */
/*   Updated: 2024/11/03 10:20:39 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_intersection(t_config *data, double xintercept, double hintercept)
{
	char	cell_value;
	int		mapgridindex_x;
	int		mapgridindex_y;

	if (data == NULL || data->map == NULL)
		return (0);
	mapgridindex_x = (int)floor(xintercept / data->size);
	mapgridindex_y = (int)floor(hintercept / data->size);
	if (mapgridindex_y < 0 || mapgridindex_y >= data->map->map_height)
		return (0);
	if (data->map->map_buffer[mapgridindex_y]
		&& mapgridindex_x < 
		(int)ft_strlen(data->map->map_buffer[mapgridindex_y]))
	{
		cell_value = data->map->map_buffer[mapgridindex_y][mapgridindex_x];
		if (cell_value == '1' || cell_value == 'D' || cell_value == '4')
			return (0);
	}
	return (1);
}

void	initialize_variables(t_config **data)
{
	(*data)->ray.ray_ngl = normalizeangle((*data)->ray.ray_ngl);
	(*data)->chek_orizental.israyfacingdown = ((*data)->ray.ray_ngl > 0
			&& (*data)->ray.ray_ngl < M_PI);
	(*data)->chek_orizental.israyracingup = 
		!(*data)->chek_orizental.israyfacingdown;
	(*data)->chek_orizental.israyfacingright = ((*data)->ray.ray_ngl < 0.5
			* M_PI || (*data)->ray.ray_ngl > 1.5 * M_PI);
	(*data)->chek_orizental.israyfacingleft = 
		!(*data)->chek_orizental.israyfacingright;
}

void	calculate_intercepts_and_steps(t_config **data)
{
	double	player_x;
	double	player_y;

	player_x = (*data)->player.x + (*data)->move_x;
	player_y = (*data)->player.y + (*data)->move_y;
	(*data)->chek_orizental.hintercept = floor((player_y / (*data)->size))
		* (*data)->size;
	if ((*data)->chek_orizental.israyfacingdown)
		(*data)->chek_orizental.hintercept += (*data)->size;
	(*data)->chek_orizental.xintercept = player_x
		+ ((*data)->chek_orizental.hintercept - player_y)
		/ tan((*data)->ray.ray_ngl);
	(*data)->chek_orizental.ystep = (*data)->size;
	if ((*data)->chek_orizental.israyracingup)
		(*data)->chek_orizental.ystep *= -1;
	(*data)->chek_orizental.xstep = (*data)->size / tan((*data)->ray.ray_ngl);
	if (((*data)->chek_orizental.israyfacingright
			&& (*data)->chek_orizental.xstep < 0)
		|| ((*data)->chek_orizental.israyfacingleft
			&& (*data)->chek_orizental.xstep > 0))
		(*data)->chek_orizental.xstep *= -1;
}

int	if_conditon(t_config **data)
{
	(*data)->chek_orizental.xtocheck = (*data)->chek_orizental.xintercept;
	if ((*data)->chek_orizental.israyracingup)
		(*data)->chek_orizental.ytocheck = 
			(*data)->chek_orizental.hintercept - 1;
	else
		(*data)->chek_orizental.ytocheck = 
			(*data)->chek_orizental.hintercept;
	if (!check_intersection(*data, (*data)->chek_orizental.xtocheck,
			(*data)->chek_orizental.ytocheck))
		return (1);
	return (0);
}

double	check_horizontal(t_config **data, int i)
{
	initialize_variables(data);
	calculate_intercepts_and_steps(data);
	while ((*data)->chek_orizental.xintercept >= 0
		&& (*data)->chek_orizental.xintercept 
		<= ((*data)->map->map_width * SIZE_) 
		&& (*data)->chek_orizental.hintercept >= 0
		&& (*data)->chek_orizental.hintercept 
		<= ((*data)->map->map_height * SIZE_))
	{
		if (if_conditon(data) == 1)
			break ;
		else
		{
			(*data)->chek_orizental.xintercept += (*data)->chek_orizental.xstep;
			(*data)->chek_orizental.hintercept += (*data)->chek_orizental.ystep;
		}
	}
	(*data)->ray.horiz_x = (*data)->chek_orizental.xtocheck;
	(*data)->ray.horiz_y = (*data)->chek_orizental.ytocheck;
	(*data)->rays[i].horiz_x = (*data)->chek_orizental.xtocheck;
	(*data)->rays[i].horiz_y = (*data)->chek_orizental.ytocheck;
	return (distancebetweenpoints((*data)->player.x + (*data)->move_x,
			(*data)->player.y + (*data)->move_y,
			(*data)->chek_orizental.xintercept,
			(*data)->chek_orizental.hintercept));
}
