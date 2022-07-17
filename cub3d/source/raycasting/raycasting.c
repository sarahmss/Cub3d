/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 17:58:28 by smodesto          #+#    #+#             */
/*   Updated: 2022/07/17 17:57:15 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static t_raycasting	hit_aux(t_raycasting r, t_side s, t_point next_touch)
{
	r.hit_side = s;
	r.wall_hit = next_touch;
	return (r);
}

/*
	@brief: defines if ray its a wall
		@param: w = map_width * TILE_SIZE
		@param: h = map_height * TILE_SIZE
		@param: s = HORIZONTAL / VERTICAL
*/
t_raycasting	hit(t_raycasting r, t_side s, int w, int h)
{
	t_raycasting	r_local;
	t_point			next_touch;
	t_point			map;

	r_local = r;
	r_local.wall_hit.x = 0;
	r_local.wall_hit.y = 0;
	r_local.intercept = set_intercept(r_local.ray_angle, r_local.player.pos, s);
	r_local.step = set_step(r_local.ray_angle, s);
	next_touch = r_local.intercept;
	while ((next_touch.x >= 0 && next_touch.x <= w)
		&& (next_touch.y >= 0 && next_touch.y <= h))
	{
		map = set_map(r_local.ray_angle, next_touch, s);
		if (r.cub_map[(int)map.y][(int)map.x] == WALL)
			return (hit_aux(r_local, s, next_touch));
		next_touch.x += r_local.step.x;
		next_touch.y += r_local.step.y;
	}
	return (r_local);
}

t_raycasting	raycasting(t_cub3d *data, double ray_angle)
{
	t_raycasting	r_h;
	t_raycasting	r_v;
	double			h_dist;
	double			v_dist;

	r_h = data->r;
	r_v = data->r;
	r_h.ray_angle = ray_angle;
	r_v.ray_angle = ray_angle;
	r_h = hit(r_h, HORIZONTAL, data->scene->map_width * TILE_SIZE,
			data->scene->map_height * TILE_SIZE);
	r_v = hit(r_v, VERTICAL, data->scene->map_width * TILE_SIZE,
			data->scene->map_height * TILE_SIZE);
	h_dist = distance_between_points(r_h.player.pos, r_h.wall_hit);
	v_dist = distance_between_points(r_v.player.pos, r_v.wall_hit);
	r_v.distance = v_dist;
	r_h.distance = h_dist;
	if (v_dist < h_dist)
		return (r_v);
	return (r_h);
}

void	cast_all_rays(t_cub3d *data)
{
	t_point			pixel_ray;
	t_raycasting	*rays;
	double			fov;
	double			ray_angle;

	pixel_ray.y = data->scene->map_width * TILE_SIZE / WALL_STRIP_WIDTH;
	rays = malloc(sizeof(t_raycasting) * pixel_ray.y);
	fov = 60 * (M_PI / 180);
	ray_angle = data->r.player.rotation_angle - (fov / 2);
	pixel_ray.x = -1;
	while (++pixel_ray.x < pixel_ray.y)
	{
		rays[(int)pixel_ray.x] = raycasting(data, ray_angle);
		ray_angle += fov / pixel_ray.y ;
	}
	data->rays = rays;
	data->num_rays = pixel_ray.y;
}
