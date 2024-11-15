/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:38:31 by ahamdi            #+#    #+#             */
/*   Updated: 2024/10/29 19:25:55 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	while_loop(t_config **data, int i, int j, int player_x)
{
	int	x;
	int	y;
	int	player_y;

	player_y = (*data)->player.y + (*data)->move_y;
	y = i * SIZE_;
	if (y > (player_y - 100) && y < (player_y + 100))
	{
		x = j * SIZE_;
		if ((x > (player_x - 100) && x < (player_x + 100)))
		{
			if ((*data)->map->map_buffer[i][j] == '1')
				draw_square(data, x - (player_x - 100),
					y - (player_y - 100), WHI);
			else if ((*data)->map->map_buffer[i][j] == 'D')
				draw_square(data, x - (player_x - 100), y - (player_y - 100),
					BLU);
			else
				draw_square(data, x - (player_x - 100), y - (player_y - 100),
					GREY);
		}
	}
}

void	draw_minimap(t_config **data)
{
	int	i;
	int	j;
	int	y;
	int	player_x;
	int	player_y;

	i = 0;
	draw_card(*data);
	player_x = (*data)->player.x + (*data)->move_x;
	player_y = (*data)->player.y + (*data)->move_y;
	while ((*data)->map->map_buffer[i])
	{
		j = 0;
		y = i * SIZE_;
		while ((*data)->map->map_buffer[i][j])
		{
			while_loop(data, i, j, player_x);
			j++;
		}
		i++;
	}
	draw_square_player(data, ((*data)->player.x / 2) - 
		(((*data)->player.x / 2) - 100), 
		((*data)->player.y / 2) - (((*data)->player.y / 2) - 100), ORNG);
}

void	draw_centered_image(t_config *data, mlx_texture_t *texture)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	*arr;

	arr = (uint32_t *)texture->pixels;
	y = 0;
	while (y < texture->height)
	{
		x = 0;
		while (x < texture->width)
		{
			if ((arr[y * texture->width + x] & 0xFF000000) != 0)
			{
				mlx_put_pixel(data->img, ((data->width_window - texture->width)
						/ 2) + x, (data->height_window - texture->height) + y,
					reverse_bytes(arr[y * texture->width + x]));
			}
			x++;
		}
		y++;
	}
}

int	close_window(t_config **data)
{
	mlx_delete_texture((*data)->texture_close_dor);
	mlx_delete_texture((*data)->texture_open_dor);
	mlx_delete_texture((*data)->texture_toush);
	mlx_delete_texture((*data)->texture_east);
	mlx_delete_texture((*data)->texture_west);
	mlx_delete_texture((*data)->texture_north);
	mlx_delete_texture((*data)->texture_south);
	mlx_delete_texture((*data)->texture_pa);
	mlx_delete_texture((*data)->texture_r);
	if ((*data)->img)
		mlx_delete_image((*data)->mlx_ptr, (*data)->img);
	if ((*data)->mlx_ptr)
		mlx_close_window((*data)->mlx_ptr);
	ft_putstr_fd(" close window\n", 1);
	destroy_data(data);
	exit(0);
}
