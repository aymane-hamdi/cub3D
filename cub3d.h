/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:48:09 by ahamdi            #+#    #+#             */
/*   Updated: 2024/11/03 11:06:05 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include "getNextLine/get_next_line.h"
# include "mlx/include/MLX42/MLX42.h"
# include <math.h>

# define FOV 60
# define S_W 1900
# define S_H 1000
# define TILE_SIZE 10
# define SIZE_ 10
# define RAY_STEP   0.0017453292519943295  //M_PI / 1800 
# define PLAYER_SPEED  2
# define PLAYER_SPEED_MINI_MAP PLAYER_SPEED 
# define ROTATION_SPEED 0.05
# define TRUE 1
# define FALSE 0 
# define TWO_PI  6.283185307179586 //2.0 * M_PI
# define BLK 0x000000FF
# define GREY 0x808080
# define BLU 0x87CEEBFF
# define GREN 0x008000FF
# define ORNG 0xFF9300FF
# define RED 0xFF0000FF
# define WHI 0xFFFFF
# define NUM_RAYS 1000

typedef struct s_map
{
	char		**map_buffer;
	int			map_width;
	int			map_height;
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	int			*floor_color;
	int			*ceiling_color;
}		t_map;
typedef struct s_chek_orizental
{
	int		israyfacingdown;
	int		israyracingup;
	int		israyfacingright;
	int		israyfacingleft;
	double	xintercept;
	double	hintercept;
	double	xstep;
	double	ystep;
	double	xtocheck;
	double	ytocheck;
}	t_chek_orizental;

typedef struct s_chek_vertical
{
	int		israyfacingdown;
	int		israyracingup;
	int		israyfacingright;
	int		israyfacingleft;
	double	vintercept;
	double	yintercept;
	double	xstep;
	double	ystep;
	double	xtocheck;
	double	ytocheck;
}t_chek_chek_vertical;
typedef struct s_ray
{
	int		index;
	double	ray_ngl;
	double	horiz_x;
	double	horiz_y;
	double	vert_x;
	double	vert_y;
	double	distance;
	int		flag;
}	t_ray;
typedef struct s_palyer
{
	int			x;
	int			y;
	double		x_mini;
	double		y_mini;
	double		angle;
	double		fov_rd;
}		t_player;
typedef struct s_config
{
	t_map					*map;
	char					**maps;
	int						counter;
	void					*img;
	int						fd_map;
	void					*mlx_ptr;
	double					width_window;
	double					height_window;
	double					mouv_camera_left;
	double					move_x;
	double					move_y;
	mlx_texture_t			*texture_north;
	mlx_texture_t			*texture_south;
	mlx_texture_t			*texture_west;
	mlx_texture_t			*texture_east;
	mlx_texture_t			*texture_toush;
	mlx_texture_t			*texture_open_dor;
	mlx_texture_t			*texture_close_dor;
	mlx_texture_t			*texture_pa;
	mlx_texture_t			*texture_r;
	double					wall_h;
	int						size;
	int						dor_x;
	int						dor_y;
	int						mouv_down;
	int						mouv_up;
	t_player				player;
	t_ray					ray;
	int						player_direction;
	int						p_d_count;
	t_ray					*rays;
	int						floor_color;
	int						ceiling_color;
	t_chek_orizental		chek_orizental;
	t_chek_chek_vertical	chek_vertical;
	int						flag;
	int						dist;
	int						end_x;
	int						f;
	int						end_y;
	char					*path;
	int						config_count;
	int						map_size;
}		t_config;
void			hook(void *ml);
void			free_strings(char **strings, size_t count);
void			error_invalid(void);
void			init_fc(t_config *config, char *line, int i, char *fc_config);
void			error_intalis(t_config **data);
void			struct_instialisation(t_config *config, char *path);
void			open_fd(char *path, int *fd);
void			map_inistialisation(t_config *config, int *fd);
void			errr(void);
void			determine_engle(t_config **data, int i, int j);
int				rgb_to_hex(int r, int g, int b);
void			rotate_player(t_config **data, int i);
int				open_close_door(t_config **data);
void			mouve_d(t_config **data, double old_y, double old_x);
int				shut_(t_config **data);
mlx_texture_t	*chek_dor_avertical(t_config *mlx);
mlx_texture_t	*chek_dor_a_ori(t_config *mlx);
int				check_intersection(t_config *data, double xintercept, 
					double Hintercept);
void			draw_minimap(t_config **data);
void			my_mlx_pixel_put(t_config *data, double x, double y, int color);
mlx_texture_t	*get_texture_bonus(t_config *mlx, int flag);
void			draw_floor_ceiling(t_config *data, int ray, 
					int top_pix, int min_pix);
void			draw_enter(t_config *data, mlx_texture_t *texture);
void			draw_update(t_config **data, mlx_texture_t *texture);
void			control_mousse(t_config	**data);
void			draw(t_config **data, mlx_texture_t *texture);
void			free_doube_eraay(char **str);
void			draw_card(t_config *data);
void			destroy_data(t_config **data);
void			fontion_mlx_and_draw(t_config **data);
void			chek_argument_and_extention(int err, char *map_name);
void			get_height_map(t_config **data);
void			free_double_array(char **str);
char			*delet_newlin(char *str);
int				open_map(t_config **data);
void			error_intalis(t_config **data);
int				close_window(t_config **data);
void			draw_square(t_config **data, int x, int y, int color);
void			draw_square_player(t_config **data, int x, int y, int color);
void			castallrays(t_config **data);
double			check_vertical(t_config **data, int i);
double			check_horizontal(t_config **data, int i);
double			normalizeangle(double angle);
double			distancebetweenpoints(double x1, double y1, 
					double x2, double y2);
void			render_wall(t_config **data, int ray, double distance,
					double angle);
void			chek_door(t_config **data);
void			draw_centered_image(t_config *data, mlx_texture_t *texture);
int				reverse_bytes(int c);
char			**spliter(char *str);
int				*init_color(char **tab);
void			check_extenstion(char *exe, int ac);
int				find_new_line(char *str);
char			*ft_first_line(char *first_str);
char			*ft_last_line(char *last_str);
void			check_colors(t_config *config);
void			check_extenstion(char *exe, int ac);
int				check_config(char **line, t_config **map);
int				check_line(char **tmp_map, char *line);
void			map_data_check(t_config *config);
void			check_valid_map(t_config *config);
void			check_map(t_config *config);
void			check_player(t_config *config);
void			check_space(t_config *config, int i, int j);
int				check_map_row_start(char *map_line);
int				skip_line(char *line);
void			free_line(char **line);
int				line_len(char **line);
void			set_directions(char **identifier, char *line);
void			init_fc(t_config *config, char *line, int i, char *fc_config);
int				check_chars(char *line);
void			isolate_map_area(t_config *config);
void			check_doors(char **map);
int				row(char *line);
#endif
