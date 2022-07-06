/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_point.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 22:02:37 by smodesto          #+#    #+#             */
/*   Updated: 2022/07/05 19:11:53 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
	Defines ray vector dir + cam_plane * mult;
*/
t_point	set_ray(t_point dir, t_point cam_plane, int pixel)
{
	double		mult;
	t_point		ray;

	mult = 2 * pixel / (double)WIN_WIDTH - 1;
	ray.x = dir.x + (cam_plane.x * mult);
	ray.y = dir.y + (cam_plane.y * mult);
	return (ray);
}

/*
	delta_ds: distance ray have to travel to go from 1 side of square to the
	next one
*/
t_point	set_delta_ds(t_point ray)
{
	t_point	delta_ds;

	if (ray.x == 0)
		delta_ds.x = 1e30;
	else
		delta_ds.x = abs((int)(1 / ray.x));
	if (ray.y == 0)
		delta_ds.y = 1e30;
	else
		delta_ds.y = abs((int)(1 / ray.y));
	return (delta_ds);
}

t_point	set_step(t_point ray)
{
	t_point	step;

	if (ray.x < 0)
		step.x = -1;
	else
		step.x = 1;
	if (ray.y < 0)
		step.y = -1;
	else
		step.y = 1;
	return (step);
}

/*
	side_ds: distance ray have to travel  from its start position to achieve
	closest side of next square
*/
t_point	set_side_ds(t_point ray, t_point map, t_point pos,
	t_point delta_ds)
{
	t_point	side_ds;

	if (ray.x < 0)
		side_ds.x = (pos.x - map.x) * delta_ds.x;
	else
		side_ds.x = (map.x + 1.0 - pos.x) * delta_ds.x;
	if (ray.y < 0)
		side_ds.y = (pos.y - map.y) * delta_ds.y;
	else
		side_ds.y = (map.y + 1.0 - pos.y) * delta_ds.y;
	return (side_ds);
}
