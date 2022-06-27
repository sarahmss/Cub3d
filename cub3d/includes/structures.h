/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 00:54:30 by smodesto          #+#    #+#             */
/*   Updated: 2022/06/27 10:29:46 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "./raycasting.h"
# include "./my_mlx_draw.h"
# include "./keymap.h"

# define WIN_WIDTH			640
# define WIN_HEIGHT			480

typedef struct s_line
{
	int		height;
	double	x0;
	double	y0;
	double	x1;
	double	y1;
	int		delta_x;
	int		delta_y;
	int		max;
}				t_line;

typedef struct s_image
{
	int			*img;
	char		*data_address;
	int			bpp;
	int			line_size;
	int			endian;
	int			width;
	int			height;
}				t_image;

typedef struct t_mlx
{
	void		*mlx;
	void		*win;
}				t_mlx;

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

typedef enum e_side
{
	HORIZONTAL,
	VERTICAL
}			t_side;

typedef struct s_point
{
	double	x;
	double	y;
}				t_point;

typedef struct s_raycasting
{
	t_point	pos;
	t_point	dir;
	t_point	cam_plane;
	t_point	ray;
	t_point	side_ds;
	t_point	delta_ds;
	t_point	map;
	t_point	step;
	double	time;
	double	old_time;
	t_side	side;
	t_scene	*scene;
}				t_raycasting;

typedef struct s_cub3d
{
	t_scene		*scene;
	t_mlx		*mlx;
	t_image		*img;
}				t_cub3d;
#endif
