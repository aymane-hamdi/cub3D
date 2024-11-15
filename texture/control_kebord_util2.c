/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_kebord_util2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:10:56 by ahamdi            #+#    #+#             */
/*   Updated: 2024/10/23 17:34:24 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	control_mousse(t_config **data)
{
	int	delta_x;
	int	x;
	int	y;

	mlx_get_mouse_pos((*data)->mlx_ptr, &x, &y);
	delta_x = x - ((*data)->width_window / 2);
	(*data)->mouv_camera_left += delta_x / 600.0;
	if ((*data)->player.angle + (*data)->mouv_camera_left >= 2 * M_PI)
		(*data)->mouv_camera_left -= 2 * M_PI;
	else if ((*data)->player.angle + (*data)->mouv_camera_left < 0)
		(*data)->mouv_camera_left += 2 * M_PI;
	mlx_set_mouse_pos((*data)->mlx_ptr, (*data)->width_window / 2,
		(*data)->height_window / 2);
}

void	fontion_mlx_and_draw(t_config **data)
{
	draw(data, (*data)->texture_r);
	mlx_loop_hook((*data)->mlx_ptr, hook, data);
	mlx_set_cursor_mode((*data)->mlx_ptr, MLX_MOUSE_HIDDEN);
}

int	rgb_to_hex(int r, int g, int b)
{
	int	a;

	a = 255;
	return ((r << 24) | (g << 16) | (b << 8) | a);
}
