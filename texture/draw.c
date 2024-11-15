/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 14:45:00 by ahamdi            #+#    #+#             */
/*   Updated: 2024/10/23 17:39:33 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	determine_engle(t_config **data, int i, int j)
{
	if ((*data)->map->map_buffer[i][j] == 'E')
		(*data)->player.angle = 90;
	if ((*data)->map->map_buffer[i][j] == 'N')
		(*data)->player.angle = 0;
	if ((*data)->map->map_buffer[i][j] == 'W')
		(*data)->player.angle = 270;
	if ((*data)->map->map_buffer[i][j] == 'S')
		(*data)->player.angle = 180;
}

void	draw(t_config **data, mlx_texture_t *texture)
{
	((*data)->img = mlx_new_image((*data)->mlx_ptr, (*data)->width_window,
				(*data)->height_window));
	if (!((*data)->img))
		error_intalis(data);
	castallrays(data);
	draw_minimap(data);
	draw_centered_image(*data, texture);
	if (mlx_image_to_window((*data)->mlx_ptr, (*data)->img, 0, 0) == -1)
		error_intalis(data);
}

void	draw_update(t_config **data, mlx_texture_t *texture)
{
	((*data)->img = mlx_new_image((*data)->mlx_ptr, (*data)->width_window,
				(*data)->height_window));
	if (!((*data)->img))
		error_intalis(data);
	castallrays(data);
	draw_minimap(data);
	draw_centered_image(*data, texture);
	if (mlx_image_to_window((*data)->mlx_ptr, (*data)->img, 0, 0) == -1)
		error_intalis(data);
}
