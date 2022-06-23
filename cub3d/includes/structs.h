/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 08:51:24 by smodesto          #+#    #+#             */
/*   Updated: 2022/06/22 22:39:55 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# define WIN_WIDTH		1280
# define WIN_HEIGHT		600
# define MENU_WIDTH		200

# define WIN_CENTER_X	400
# define WIN_CENTER_Y	300

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

typedef struct s_vector
{
	double	x0;
	double	y0;
	double	x1;
	double	y1;
	int		del_x;
	int		del_y;
	int		module;
}				t_vector;

/*
For our player we have:
	fov: Field of vision (ø = 66°)
	pos: position vector
	dir: direction vector
	cam_plane: tg(ø)·dir(perpendicular to the direction, with variable len)
	cam_pixel == (mult·cam_plane) vector from (xd, yd)→(x_pixel, y_pixel)
	mult == (2·(act_pixel/WIN_WIDTH) - 1) escalar used to find ray
	ray == (dir + cam_pixel)
  012345689ABCD
 |---pixels----|
  _____________	→ (cam_plane)
  \		|(dir)/
   \	|    /
	\	|   /
	 \  |  /	→(ray)
	  \ | /
	   \|/
	    P		→(pos)

*/
typedef struct s_raycasting
{
	t_vector	pos;
	t_vector	dir;
	t_vector	cam_plane;
	t_vector	cam_pixel;
	t_vector	ray;
	int			mult;
	int			fov;
	double		time;
	double		old_time;
}				t_raycasting;

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

typedef struct s_cub3d
{
	void		*mlx;
	void		*win;
	t_scene		*scene;
}				t_cub3d;

#endif
