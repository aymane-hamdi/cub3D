/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_kebord_util1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:07:03 by ahamdi            #+#    #+#             */
/*   Updated: 2024/10/29 19:31:08 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	mouve_w(t_config **data, double old_y, double old_x)
{
	double	new_x;
	double	new_y;

	new_x = ((*data)->player.x + (*data)->move_x + cos((*data)->player.angle
				+ (*data)->mouv_camera_left) * PLAYER_SPEED) / (*data)->size;
	new_y = ((*data)->player.y + (*data)->move_y + sin((*data)->player.angle
				+ (*data)->mouv_camera_left) * PLAYER_SPEED) / (*data)->size;
	if ((*data)->map->map_buffer[(int)old_y]
		&& (*data)->map->map_buffer[(int)old_y][(int)new_x] != '1'
		&& (*data)->map->map_buffer[(int)old_y][(int)new_x] != 'D'
		&& (*data)->map->map_buffer[(int)new_y]
		&& (*data)->map->map_buffer[(int)new_y][(int)old_x] != '1'
		&& (*data)->map->map_buffer[(int)new_y][(int)old_x] != 'D'
		&& (*data)->map->map_buffer[(int)new_y][(int)new_x])
	{
		(*data)->move_x += cos((*data)->player.angle
				+ (*data)->mouv_camera_left) * PLAYER_SPEED;
		(*data)->move_y += sin((*data)->player.angle
				+ (*data)->mouv_camera_left) * PLAYER_SPEED;
	}
}

void	mouve_s(t_config **data, double old_y, double old_x)
{
	double	new_x;
	double	new_y;

	new_x = ((*data)->player.x + (*data)->move_x - cos((*data)->player.angle
				+ (*data)->mouv_camera_left) * PLAYER_SPEED) / (*data)->size;
	new_y = ((*data)->player.y + (*data)->move_y - sin((*data)->player.angle
				+ (*data)->mouv_camera_left) * PLAYER_SPEED) / (*data)->size;
	if ((*data)->map->map_buffer[(int)old_y]
		&& (*data)->map->map_buffer[(int)old_y][(int)new_x] != '1'
		&& (*data)->map->map_buffer[(int)old_y][(int)new_x] != 'D'
		&& (*data)->map->map_buffer[(int)new_y]
		&& (*data)->map->map_buffer[(int)new_y][(int)old_x] != '1'
		&& (*data)->map->map_buffer[(int)new_y][(int)old_x] != 'D'
		&& (*data)->map->map_buffer[(int)new_y][(int)new_x])
	{
		(*data)->move_x -= cos((*data)->player.angle
				+ (*data)->mouv_camera_left) * PLAYER_SPEED;
		(*data)->move_y -= sin((*data)->player.angle
				+ (*data)->mouv_camera_left) * PLAYER_SPEED;
	}
}

void	mouve_a(t_config **data, double old_y, double old_x)
{
	double	new_x;
	double	new_y;

	new_x = ((*data)->player.x + (*data)->move_x + sin((*data)->player.angle
				+ (*data)->mouv_camera_left) * PLAYER_SPEED) / (*data)->size;
	new_y = ((*data)->player.y + (*data)->move_y - cos((*data)->player.angle
				+ (*data)->mouv_camera_left) * PLAYER_SPEED) / (*data)->size;
	if ((*data)->map->map_buffer[(int)old_y]
		&& (*data)->map->map_buffer[(int)old_y][(int)new_x] != '1'
		&& (*data)->map->map_buffer[(int)old_y][(int)new_x] != 'D'
		&& (*data)->map->map_buffer[(int)new_y]
		&& (*data)->map->map_buffer[(int)new_y][(int)old_x] != '1'
		&& (*data)->map->map_buffer[(int)new_y][(int)old_x] != 'D'
		&& (*data)->map->map_buffer[(int)new_y][(int)new_x])
	{
		(*data)->move_x += sin((*data)->player.angle
				+ (*data)->mouv_camera_left) * PLAYER_SPEED;
		(*data)->move_y -= cos((*data)->player.angle
				+ (*data)->mouv_camera_left) * PLAYER_SPEED;
	}
}

static int	if_condition(t_config **data, double old_y, double old_x)
{
	if (mlx_is_mouse_down((*data)->mlx_ptr, 0))
		return (shut_(data));
	if (mlx_is_key_down((*data)->mlx_ptr, MLX_KEY_UP))
		(*data)->mouv_up += 5;
	else if (mlx_is_key_down((*data)->mlx_ptr, MLX_KEY_DOWN))
		(*data)->mouv_up -= 5;
	else if (open_close_door(data) == 1)
		return (1);
	else if (mlx_is_key_down((*data)->mlx_ptr, 256))
		close_window(data);
	else if (mlx_is_key_down((*data)->mlx_ptr, MLX_KEY_RIGHT))
		rotate_player(data, 1);
	else if (mlx_is_key_down((*data)->mlx_ptr, MLX_KEY_LEFT))
		rotate_player(data, 0);
	else if (mlx_is_key_down((*data)->mlx_ptr, MLX_KEY_W))
		mouve_w(data, old_y, old_x);
	else if (mlx_is_key_down((*data)->mlx_ptr, MLX_KEY_S))
		mouve_s(data, old_y, old_x);
	else if (mlx_is_key_down((*data)->mlx_ptr, MLX_KEY_A))
		mouve_a(data, old_y, old_x);
	else if (mlx_is_key_down((*data)->mlx_ptr, MLX_KEY_D))
		mouve_d(data, old_y, old_x);
	return (0);
}

void	hook(void *ml)
{
	t_config	**data;
	double		old_y;
	double		old_x;

	data = ml;
	old_x = ((*data)->player.x + (*data)->move_x) / (*data)->size;
	old_y = ((*data)->player.y + (*data)->move_y) / (*data)->size;
	control_mousse(data);
	if (if_condition(data, old_y, old_x) == 1)
		return ;
	mlx_delete_image((*data)->mlx_ptr, (*data)->img);
	draw_update(data, (*data)->texture_r);
}
