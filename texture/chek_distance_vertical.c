/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chek_distance_vertical.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:37:07 by ahamdi            #+#    #+#             */
/*   Updated: 2024/10/17 11:22:07 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	initialize_variables_vertical(t_config **data)
{
	(*data)->ray.ray_ngl = normalizeangle((*data)->ray.ray_ngl);
	(*data)->chek_vertical.israyfacingdown = ((*data)->ray.ray_ngl > 0
			&& (*data)->ray.ray_ngl < M_PI);
	(*data)->chek_vertical.israyracingup
		=!(*data)->chek_vertical.israyfacingdown;
	(*data)->chek_vertical.israyfacingright = ((*data)->ray.ray_ngl < 0.5 * M_PI
			|| (*data)->ray.ray_ngl > 1.5 * M_PI);
	(*data)->chek_vertical.israyfacingleft 
		= !(*data)->chek_vertical.israyfacingright;
}

void	calculate_intercepts_and_steps_vertical(t_config **data)
{
	double	player_x;
	double	player_y;

	player_x = (*data)->player.x + (*data)->move_x;
	player_y = (*data)->player.y + (*data)->move_y;
	(*data)->chek_vertical.vintercept = floor(player_x / (*data)->size)
		* (*data)->size;
	if ((*data)->chek_vertical.israyfacingright)
		(*data)->chek_vertical.vintercept += (*data)->size;
	(*data)->chek_vertical.yintercept = player_y
		+ ((*data)->chek_vertical.vintercept - player_x)
		* tan((*data)->ray.ray_ngl);
	(*data)->chek_vertical.xstep = (*data)->size;
	if ((*data)->chek_vertical.israyfacingleft)
		(*data)->chek_vertical.xstep *= -1;
	(*data)->chek_vertical.ystep = (*data)->size * tan((*data)->ray.ray_ngl);
	if ((*data)->chek_vertical.israyracingup
		&& (*data)->chek_vertical.ystep > 0)
		(*data)->chek_vertical.ystep *= -1;
	if ((*data)->chek_vertical.israyfacingdown
		&& (*data)->chek_vertical.ystep < 0)
		(*data)->chek_vertical.ystep *= -1;
}

int	if_condition(t_config **data)
{
	(*data)->chek_vertical.ytocheck = (*data)->chek_vertical.yintercept;
	if ((*data)->chek_vertical.israyfacingleft)
		(*data)->chek_vertical.xtocheck = 
			(*data)->chek_vertical.vintercept - 1;
	else
		(*data)->chek_vertical.xtocheck = (*data)->chek_vertical.vintercept;
	if (!check_intersection(*data, (*data)->chek_vertical.xtocheck,
			(*data)->chek_vertical.ytocheck))
		return (1);
	return (0);
}

double	check_vertical(t_config **data, int i)
{
	initialize_variables_vertical(data);
	calculate_intercepts_and_steps_vertical(data);
	while ((*data)->chek_vertical.vintercept >= 0
		&& (*data)->chek_vertical.vintercept <= ((*data)->map->map_width
			* SIZE_) && (*data)->chek_vertical.yintercept >= 0
		&& (*data)->chek_vertical.yintercept <= ((*data)->map->map_height
			* SIZE_))
	{
		if (if_condition(data) == 1)
			break ;
		else
		{
			(*data)->chek_vertical.vintercept += (*data)->chek_vertical.xstep;
			(*data)->chek_vertical.yintercept += (*data)->chek_vertical.ystep;
		}
	}
	(*data)->ray.vert_x = (*data)->chek_vertical.xtocheck;
	(*data)->ray.vert_y = (*data)->chek_vertical.ytocheck;
	(*data)->rays[i].vert_x = (*data)->chek_vertical.xtocheck;
	(*data)->rays[i].vert_y = (*data)->chek_vertical.ytocheck;
	return (distancebetweenpoints((*data)->player.x + (*data)->move_x,
			(*data)->player.y + (*data)->move_y,
			(*data)->chek_vertical.vintercept,
			(*data)->chek_vertical.yintercept));
}
