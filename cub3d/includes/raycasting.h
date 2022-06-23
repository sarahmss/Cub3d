/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 22:04:46 by smodesto          #+#    #+#             */
/*   Updated: 2022/06/23 01:06:12 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

#include "../includes/cub3d.h"

typedef enum e_side
{
	HORIZONTAL,
	VERTICAL
}				t_side;

typedef struct s_point
{
	double	x;
	double	y;
}				t_point;

/*
For our player we have:
	fov: Field of vision (ø = 66°)
	pos: position vector
	dir: direction vector
	cam_plane: tg(ø)·dir(perpendicular to the direction, with variable len)
	cam_pixel == (mult·cam_plane) vector from (xd, yd)→(x_pixel, y_pixel)
	mult == (2·(act_pixel/WIN_WIDTH) - 1) escalar used to find ray
	ray == (dir + cam_pixel)
	map : actual square ray is in
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
	t_point	pos;
	t_point	dir;
	t_point	cam_plane;
	t_point	ray;
	t_point	side_ds;
	t_point	delta_ds;
	t_point	map;
	t_point	step;
	double		time;
	double		old_time;
	int			side;
}				t_raycasting;

//	Point configure
t_point	set_ray(t_point dir, t_point cam_plane, int pixel);
t_point	set_delta_ds(t_point ray);
t_point	set_step(t_point ray);
t_point	set_side_ds(t_point ray, t_point map, t_point pos,
	t_point delta_ds);

#endif
