/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 17:58:28 by smodesto          #+#    #+#             */
/*   Updated: 2022/07/09 23:39:01 by smodesto         ###   ########.fr       */
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

void	raycasting(t_cub3d *data)
{
	t_raycasting	r_h;
	t_raycasting	r_v;
	double			h_dist;
	double			v_dist;

	r_h = hit(data->r, HORIZONTAL, data->scene->map_width * TILE_SIZE,
			data->scene->map_height * TILE_SIZE);
	r_v = hit(data->r, VERTICAL, data->scene->map_width * TILE_SIZE,
			data->scene->map_height * TILE_SIZE);
	h_dist = distance_between_points(r_h.player.pos, r_h.wall_hit);
	v_dist = distance_between_points(r_v.player.pos, r_v.wall_hit);
	if (v_dist < h_dist)
	{
		data->r = r_v;
		data->r.distance = v_dist;
	}
	else
	{
		data->r = r_h;
		data->r.distance = h_dist;
	}
}

void	cast_all_rays(t_cub3d *data)
{
	int				pixel;
	int				num_rays;
	t_raycasting	*rays;
	double			fov;

	fov = 60 * (M_PI / 180);
	data->r.ray_angle = data->r.player.rotation_angle - (fov / 2);
	pixel = -1;
	num_rays = data->scene->map_width * TILE_SIZE / WALL_STRIP_WIDTH;
	rays = malloc(sizeof(t_raycasting) * num_rays);
	while (++pixel < num_rays)
	{
		raycasting(data);
		rays[pixel] = data->r;
		data->r.ray_angle += fov / num_rays ;
	}
	data->rays = rays;
	data->num_rays = num_rays;
}
