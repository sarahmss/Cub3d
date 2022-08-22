/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_point.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 22:03:40 by smodesto          #+#    #+#             */
/*   Updated: 2022/08/22 16:05:57 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
	@brief: find x and y of the closest intersection ray-wall
	@param: pos: player position
*/
t_point	set_intercept(double ray_angle, t_point pos, t_side h_v)
{
	t_point	intercept;

	if (h_v == HORIZONTAL)
	{
		intercept.y = floor(pos.y / TILE_SIZE) * TILE_SIZE;
		if (is_ray_facing_down(ray_angle))
			intercept.y += TILE_SIZE;
		intercept.x = pos.x + ((intercept.y - pos.y) / tan(ray_angle));
	}
	else
	{
		intercept.x = floor(pos.x / TILE_SIZE) * TILE_SIZE;
		if (is_ray_facing_right(ray_angle))
			intercept.x += TILE_SIZE;
		intercept.y = pos.y + (intercept.x - pos.x) * tan(ray_angle);
	}
	return (intercept);
}

/*
	@brief: Calculate the increment step.x and step.y
*/
t_point	set_step(double ray_angle, t_side h_v)
{
	t_point	step;

	if (h_v == HORIZONTAL)
	{
		step.y = TILE_SIZE;
		if (is_ray_facing_up(ray_angle))
			step.y *= -1;
		step.x = TILE_SIZE / tan(ray_angle);
		if (is_ray_facing_left(ray_angle) && step.x > 0)
			step.x *= -1;
		if (is_ray_facing_right(ray_angle) && step.x < 0)
			step.x *= -1;
	}
	else
	{
		step.x = TILE_SIZE;
		if (is_ray_facing_left(ray_angle))
			step.x *= -1;
		step.y = TILE_SIZE * tan(ray_angle);
		if (is_ray_facing_up(ray_angle) && step.y > 0)
			step.y *= -1;
		if (is_ray_facing_down(ray_angle) && step.y < 0)
			step.y *= -1;
	}
	return (step);
}

t_point	set_map(double ray_angle, t_point next_touch, t_side s, t_point wh)
{
	t_point	map;

	map.x = next_touch.x / TILE_SIZE;
	map.y = next_touch.y / TILE_SIZE;
	if ((is_ray_facing_up(ray_angle) && s == HORIZONTAL && map.y > 0)
		|| (map.y == wh.y / TILE_SIZE))
		map.y--;
	if ((is_ray_facing_left(ray_angle) && s == VERTICAL && map.x > 0)
		|| (map.x == wh.x / TILE_SIZE))
		map.x--;
	return (map);
}
