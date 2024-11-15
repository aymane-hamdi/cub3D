/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rander_util1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akheired <akheired@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:38:25 by ahamdi            #+#    #+#             */
/*   Updated: 2024/11/03 11:57:04 by akheired         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	reverse_bytes(int c)
{
	unsigned int	b;

	b = 0;
	b |= (c & 0xFF) << 24;
	b |= (c & 0xFF00) << 8;
	b |= (c & 0xFF0000) >> 8;
	b |= (c & 0xFF000000) >> 24;
	return (b);
}

void	my_mlx_pixel_put(t_config *data, double x, double y, int color)
{
	if (x >= 0 && x < data->width_window && y >= 0
		&& y < data->height_window)
		mlx_put_pixel(data->img, x, y, color);
}

void	draw_floor_ceiling(t_config *data, int ray, int top_pix, int min_pix)
{
	int	i;
	int	hig;

	hig = data->height_window;
	i = 0;
	while (i < top_pix)
	{
		my_mlx_pixel_put(data, ray, i, data->ceiling_color);
		i++;
	}
	i = min_pix;
	while (i < hig)
	{
		my_mlx_pixel_put(data, ray, i, data->floor_color);
		i++;
	}
}

mlx_texture_t	*chek_dor_a_ori(t_config *mlx)
{
	int	map_y;
	int	map_x;

	if (mlx->ray.flag == 1)
	{
		map_y = (int)floor(mlx->ray.horiz_y / TILE_SIZE);
		map_x = (int)floor(mlx->ray.horiz_x / TILE_SIZE);
		if (mlx->map->map_buffer
			&& map_y >= 0 && map_y < mlx->map->map_height
			&& mlx->map->map_buffer[map_y]
			&& map_x >= 0 && map_x < (int)ft_strlen(mlx->map->map_buffer[map_y])
			&& mlx->map->map_buffer[map_y][map_x] == 'D')
			return (mlx->texture_close_dor);
		else if (mlx->map->map_buffer
			&& map_y >= 0 && map_y < mlx->map->map_height
			&& mlx->map->map_buffer[map_y]
			&& map_x >= 0 && map_x < (int)ft_strlen(mlx->map->map_buffer[map_y])
			&& mlx->map->map_buffer[map_y][map_x] == '4')
			return (mlx->texture_open_dor);
		if (mlx->ray.ray_ngl > 0 && mlx->ray.ray_ngl < M_PI)
			return (mlx->texture_south);
		else
			return (mlx->texture_north);
	}
	return (NULL);
}

mlx_texture_t	*chek_dor_avertical(t_config *mlx)
{
	int				map_y;
	int				map_x;

	map_y = (int)floor(mlx->ray.vert_y / TILE_SIZE);
	map_x = (int)floor(mlx->ray.vert_x / TILE_SIZE);
	if (mlx->map->map_buffer
		&& map_y >= 0 && map_y < mlx->map->map_height
		&& mlx->map->map_buffer[map_y]
		&& map_x >= 0 && map_x < (int)ft_strlen(mlx->map->map_buffer[map_y])
		&& mlx->map->map_buffer[map_y][map_x] == 'D')
		return (mlx->texture_close_dor);
	else if (mlx->map->map_buffer
		&& map_y >= 0 && map_y < mlx->map->map_height
		&& mlx->map->map_buffer[map_y]
		&& map_x >= 0 && map_x < (int)ft_strlen(mlx->map->map_buffer[map_y])
		&& mlx->map->map_buffer[map_y][map_x] == '4')
		return (mlx->texture_open_dor);
	return (NULL);
}
