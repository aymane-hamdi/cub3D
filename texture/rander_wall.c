/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rander_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:06:49 by ahamdi            #+#    #+#             */
/*   Updated: 2024/10/29 19:27:25 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

mlx_texture_t	*get_texture_bonus(t_config *mlx, int flag)
{
	mlx_texture_t	*texture_or;
	mlx_texture_t	*texture_ver;

	texture_or = chek_dor_a_ori(mlx);
	texture_ver = chek_dor_avertical(mlx);
	mlx->ray.ray_ngl = normalizeangle(mlx->ray.ray_ngl);
	if (flag == 0)
	{
		if (texture_ver)
			return (texture_ver);
		else if (mlx->ray.ray_ngl > M_PI / 2 && mlx->ray.ray_ngl < 3 
			* (M_PI / 2))
			return (mlx->texture_east);
		else
			return (mlx->texture_west);
	}
	else if (texture_or)
		return (texture_or);
	return (NULL);
}

double	get_x_o(mlx_texture_t *texture, t_config *mlx)
{
	double	x_o;

	if (mlx->ray.flag == 1)
		x_o = (int)fmodf((mlx->ray.horiz_x * (texture->width / TILE_SIZE)),
				texture->width);
	else
		x_o = (int)fmodf((mlx->ray.vert_y * (texture->width / TILE_SIZE)),
				texture->width);
	return (x_o);
}

void	draw_wall(t_config *mlx, double top_pix, double min_pix, double wall_h)
{
	double			x_o;
	double			y_o;
	uint32_t		*arr;
	double			y_step;
	mlx_texture_t	*texture;

	y_o = 0;
	texture = get_texture_bonus(mlx, mlx->ray.flag);
	if (!texture)
		return ;
	arr = (uint32_t *)texture->pixels;
	y_step = (double)texture->height / wall_h;
	x_o = get_x_o(texture, mlx);
	y_o = ((top_pix - mlx->mouv_up)
			- (mlx->height_window / 2) + (wall_h / 2)) * y_step;
	if (y_o < 0)
		y_o = 0;
	while (top_pix < min_pix)
	{
		if (top_pix > 0 && top_pix < mlx->height_window)
			mlx_put_pixel(mlx->img, mlx->ray.index, top_pix,
				reverse_bytes(arr[(int)y_o * texture->width + (int)x_o]));
		y_o += y_step;
		top_pix++;
	}
}

void	render_wall(t_config **data, int ray, double distance, double angle)
{
	double	wall_h;
	double	min_pix;
	double	top_pix;

	(void)angle;
	(*data)->ray.index = ray;
	distance *= cos(normalizeangle(angle - ((*data)->player.angle
					+ (*data)->mouv_camera_left)));
	(*data)->ray.distance = distance;
	wall_h = ((*data)->size / distance) * (((*data)->width_window / 2)
			/ tan((*data)->player.fov_rd / 2));
	min_pix = ((*data)->height_window / 2) + (wall_h / 2);
	top_pix = ((*data)->height_window / 2) - (wall_h / 2);
	top_pix += (*data)->mouv_up;
	min_pix += (*data)->mouv_up;
	if (min_pix > (*data)->height_window)
		min_pix = (*data)->height_window;
	if (top_pix < 0)
		top_pix = 0;
	draw_wall(*data, top_pix, min_pix, wall_h);
	draw_floor_ceiling(*data, ray, top_pix, min_pix);
}
