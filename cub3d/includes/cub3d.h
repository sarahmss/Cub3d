/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 23:29:38 by smodesto          #+#    #+#             */
/*   Updated: 2022/07/29 00:13:17 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "../libraries/minilibx-linux/mlx.h"
# include "../libraries/libft/libft.h"
# include "./raycasting.h"
# include "./my_mlx_draw.h"
# include "./keymap.h"

typedef struct s_render_map
{
	t_point	iterator;
	t_point	tile;
	t_point	tile_size;
	int		color;
}	t_render_map;

typedef enum e_map
{
	EMPTY,
	WALL,
	N,
	S,
	W,
	E,
	SPACES,
	TAB
}				t_map;

typedef enum e_textures
{
	T_NO,
	T_SO,
	T_WE,
	T_EA
}		t_textures;

typedef struct s_scene
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		floor_color[3];
	int		ceiling_color[3];
	int		map_height;
	int		map_width;
	int		**cub_map;
}			t_scene;

/*
	rays: all rays beeing casted (cleaned in each frame)
	r: store information about this frame
*/
typedef struct s_cub3d
{
	t_scene			*scene;
	t_mlx			*mlx;
	t_image			*img;
	t_image			*background;
	t_raycasting	r;
	t_raycasting	*rays;
	int				num_rays;
	int				win_width;
	int				win_height;
	double			fov;
	t_image			*textures[4];
}				t_cub3d;

//	textures
int				get_facing_side(double ray_angle, t_side side);
int				get_x_offset(t_raycasting ray);
int				check_x_inverse_offset(t_raycasting ray, int texture_offset);
int				handle_textures(t_cub3d *data, t_image *text[4]);
int				get_wall_pixel_color(t_image *texture, int offset_x,
					int offset_y);
void			init_background(t_cub3d *data, int width, int height,
					t_scene *s);
void			copy_layer(t_image *from, t_image *to, t_point win);

//	init
t_cub3d			*init_data(char *argv);
int				check_error(int err, char *msg);
int				before_living(t_cub3d *data);
void			print_map(int w, int h, int **map);

//	Parsing
int				read_file(char *filename, t_scene *scene);
int				map_parsing(char **cub_map, t_scene *scene);
int				check_map(char **cub_map, t_scene *scene);
int				get_elements(t_scene *scene, int fd, int i);

//	events
void			control_events(t_cub3d *data);
void			move_left(t_cub3d *data, t_raycasting r);
void			move_right(t_cub3d *data, t_raycasting r);

//	img
void			ft_create_image(t_mlx *mlx, t_image *img, int width,
					int height);
void			draw_game(t_cub3d *data, t_mlx *mlx, t_image *img);
void			background(t_image *img, int f[3], int c[3], t_point wh);
void			draw_minimap(t_cub3d *data, t_scene *scene, t_image *img);

// raycasting.c
void			cast_all_rays(t_cub3d *data);
t_raycasting	define_points(t_scene *scn);
void			render_walls(t_cub3d *data, t_point init, t_point end,
					t_point win);

// controls
void			move_forward(t_cub3d *data, t_raycasting r);
void			move_backward(t_cub3d *data, t_raycasting r);
void			rotate_right(t_cub3d *data);
void			rotate_left(t_cub3d *data);

#endif
