/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 10:01:44 by ahamdi            #+#    #+#             */
/*   Updated: 2024/10/20 10:08:30 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	error_intalis(t_config **data)
{
	ft_putstr_fd("Failed to initialize mlx.\n", 2);
	destroy_data(data);
	exit(1);
}

void	struct_instialisation(t_config *config, char *path)
{
	config->map = ft_calloc (1, sizeof(t_map));
	config->map->north_texture = NULL;
	config->map->south_texture = NULL;
	config->map->west_texture = NULL;
	config->map->east_texture = NULL;
	config->map->floor_color = NULL;
	config->map->ceiling_color = NULL;
	config->map->map_height = 0;
	config->config_count = 0;
	config->path = path;
	config->size = TILE_SIZE;
	config->p_d_count = 0;
}

void	open_fd(char *path, int *fd)
{
	*fd = open(path, O_RDONLY);
	if (*fd <= 0)
	{
		perror("open");
		exit(1);
	}
}

char	*chek_lin(t_config *config, int *fd)
{
	char	*line;

	line = get_next_line(*fd);
	if (!line)
	{
		ft_putstr_fd("empty map\n", 2);
		close (*fd);
		free(config->map);
		free(config);
		exit (1);
	}
	return (line);
}

void	map_inistialisation(t_config *config, int *fd)
{
	int		i;
	char	*line;

	i = 0;
	line = chek_lin(config, fd);
	while (1)
	{
		if (!line)
			break ;
		config->map->map_height++;
		free(line);
		line = get_next_line(*fd);
	}
	close(*fd);
	open_fd(config->path, fd);
	config->maps = ft_calloc(config->map->map_height + 1, sizeof(char *));
	config->maps[config->map->map_height] = NULL;
	while (1)
	{
		config->maps[i] = get_next_line(*fd);
		if (!config->maps[i++])
			break ;
	}
	close(*fd);
}
