/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 19:18:40 by ahamdi            #+#    #+#             */
/*   Updated: 2024/11/03 10:43:24 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	inial_texturs1(t_config *data)
{
	data->counter = 0;
	close(data->f);
	data->width_window = 1900;
	data->height_window = 1000;
	data->texture_north = mlx_load_png(data->map->north_texture);
	if (!data->texture_north)
		error_intalis(&data);
	data->texture_west = mlx_load_png(data->map->west_texture);
	if (!data->texture_west)
		error_intalis(&data);
	data->texture_south = mlx_load_png(data->map->south_texture);
	if (!data->texture_south)
		error_intalis(&data);
	data->texture_east = mlx_load_png(data->map->east_texture);
	if (!data->texture_east)
		error_intalis(&data);
	data->texture_open_dor = mlx_load_png("textures/open__dor.png");
	if (!data->texture_open_dor)
		error_intalis(&data);
	data->texture_close_dor = mlx_load_png("textures/close__door.png");
	if (!data->texture_close_dor)
		error_intalis(&data);
	data->texture_r = mlx_load_png("textures/1.png");
	if (!data->texture_r)
		error_intalis(&data);
}

void	inial_textures(t_config *data)
{
	inial_texturs1(data);
	data->texture_pa = mlx_load_png("textures/2.png");
	if (!data->texture_pa)
		error_intalis(&data);
	data->texture_toush = mlx_load_png("textures/toush.png");
	if (!data->texture_toush)
		error_intalis(&data);
	data->move_x = 0;
	data->move_y = 0;
	data->mouv_down = 0;
	data->mouv_up = 0;
	data->dor_x = -1;
	data->dor_y = -1;
	data->player.fov_rd = (FOV * M_PI) / 180;
	data->map->map_width = ft_strlen(data->map->map_buffer[0]);
	data->ceiling_color = rgb_to_hex(data->map->ceiling_color[0], 
			data->map->ceiling_color[1], data->map->ceiling_color[2]);
	data->floor_color = rgb_to_hex(data->map->floor_color[0], 
			data->map->floor_color[1], data->map->floor_color[2]);
}

void	intail_parsin(int ac, char **av, t_config	*data)
{
	check_extenstion(av[1], ac);
	open_fd(av[1], &data->fd_map);
	struct_instialisation(data, av[1]);
	map_inistialisation(data, &data->fd_map);
	map_data_check(data);
	isolate_map_area(data);
	check_map(data);
	check_player(data);
	check_valid_map(data);
	inial_textures(data);
}

int	main(int ac, char **av)
{
	t_config	*data;

	data = ft_calloc(1, sizeof(t_config));
	if (!data)
	{
		ft_putstr_fd("Error: Memory allocation failed\n", 2);
		exit(1);
	}
	intail_parsin(ac, av, data);
	data->mlx_ptr = mlx_init(data->width_window,
			data->height_window, "cub_3d", true);
	if (!data->mlx_ptr)
		error_intalis(&data);
	data->rays = ft_calloc(data->width_window, sizeof(t_ray));
	if (!data->rays)
	{
		ft_putstr_fd("Error: Memory allocation failed\n", 2);
		destroy_data(&data);
		exit(1);
	}
	fontion_mlx_and_draw(&data);
	mlx_loop(data->mlx_ptr);
	mlx_terminate(data->mlx_ptr);
}
