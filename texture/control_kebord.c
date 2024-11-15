/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_kebord.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 20:49:12 by ahamdi            #+#    #+#             */
/*   Updated: 2024/10/29 19:30:21 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	rotate_player(t_config **data, int i)
{
	if (i == 1)
	{
		(*data)->mouv_camera_left += ROTATION_SPEED;
		if ((*data)->player.angle + (*data)->mouv_camera_left > 2 * M_PI)
			(*data)->mouv_camera_left -= 2 * M_PI;
	}
	else
	{
		(*data)->mouv_camera_left -= ROTATION_SPEED;
		if ((*data)->player.angle + (*data)->mouv_camera_left < 0)
			(*data)->mouv_camera_left += 2 * M_PI;
	}
}

int	condtion(t_config **data)
{
	chek_door(data);
	if ((*data)->dor_x == -1 && (*data)->dor_y == -1)
		return (1);
	else if ((*data)->dor_y != 0
		&& (*data)->dor_x != (*data)->map->map_width - 1
		&& (*data)->dor_y != (*data)->map->map_height - 1)
	{
		(*data)->map->map_buffer[(*data)->dor_y][(*data)->dor_x] = 'D';
		mlx_delete_image((*data)->mlx_ptr, (*data)->img);
		draw_update(data, (*data)->texture_r);
	}
	return (1);
}

int	open_close_door(t_config **data)
{
	if (mlx_is_key_down((*data)->mlx_ptr, MLX_KEY_O))
	{
		chek_door(data);
		if ((*data)->dor_x == -1 && (*data)->dor_y == -1)
			return (1);
		else if ((*data)->dor_y != 0
			&& (*data)->dor_x != (*data)->map->map_width - 1
			&& (*data)->dor_y != (*data)->map->map_height - 1)
		{
			(*data)->map->map_buffer[(*data)->dor_y][(*data)->dor_x] = '4';
			mlx_delete_image((*data)->mlx_ptr, (*data)->img);
			draw_update(data, (*data)->texture_r);
		}
		return (1);
	}
	else if (mlx_is_key_down((*data)->mlx_ptr, MLX_KEY_C))
		return (condtion(data));
	return (0);
}

void	mouve_d(t_config **data, double old_y, double old_x)
{
	double	new_x;
	double	new_y;

	new_x = ((*data)->player.x + (*data)->move_x - sin((*data)->player.angle
				+ (*data)->mouv_camera_left) * PLAYER_SPEED) / (*data)->size;
	new_y = ((*data)->player.y + (*data)->move_y + cos((*data)->player.angle
				+ (*data)->mouv_camera_left) * PLAYER_SPEED) / (*data)->size;
	if ((*data)->map->map_buffer[(int)old_y]
		&& (*data)->map->map_buffer[(int)old_y][(int)new_x] != '1'
		&& (*data)->map->map_buffer[(int)old_y][(int)new_x] != 'D'
		&& (*data)->map->map_buffer[(int)new_y]
		&& (*data)->map->map_buffer[(int)new_y][(int)old_x] != '1'
		&& (*data)->map->map_buffer[(int)new_y][(int)old_x] != 'D'
		&& (*data)->map->map_buffer[(int)new_y][(int)new_x])
	{
		(*data)->move_x -= sin((*data)->player.angle
				+ (*data)->mouv_camera_left) * PLAYER_SPEED;
		(*data)->move_y += cos((*data)->player.angle
				+ (*data)->mouv_camera_left) * PLAYER_SPEED;
	}
}

int	shut_(t_config **data)
{
	static int	frame;

	mlx_delete_image((*data)->mlx_ptr, (*data)->img);
	if (frame % 5 == 0)
		draw_update(data, (*data)->texture_pa);
	else
		draw_update(data, (*data)->texture_r);
	frame++;
	return (1);
}
