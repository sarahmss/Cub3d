/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 17:58:28 by smodesto          #+#    #+#             */
/*   Updated: 2022/08/17 13:53:24 by smodesto         ###   ########.fr       */
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
t_raycasting	hit(t_raycasting r, t_side s, t_point wh)
{
	t_raycasting	r_local;
	t_point			next_touch;
	t_point			map;

	r_local = r;
	r_local.intercept = set_intercept(r_local.ray_angle, r_local.player.pos, s);
	r_local.step = set_step(r_local.ray_angle, s);
	next_touch = r_local.intercept;
	while ((next_touch.x >= 0 && next_touch.x <= wh.x)
		&& (next_touch.y >= 0 && next_touch.y <= wh.y))
	{
		map = set_map(r_local.ray_angle, next_touch, s, wh);
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
	t_point			wh;

	wh.x = data->win_width;
	wh.y = data->win_height;
	r_h = data->r;
	r_v = data->r;
	r_h.ray_angle = ray_angle;
	r_v.ray_angle = ray_angle;
	r_h = hit(r_h, HORIZONTAL, wh);
	r_v = hit(r_v, VERTICAL, wh);
	r_h.distance = distance_between_points(r_h.player.pos, r_h.wall_hit);
	r_v.distance = distance_between_points(r_v.player.pos, r_v.wall_hit);
	if (r_h.distance < r_v.distance)
		return (r_h);
	return (r_v);
}

void	cast_all_rays(t_cub3d *data)
{
	t_raycasting	*rays;
	int				pixel;
	double			ray_angle;

	rays = ft_calloc(data->num_rays, sizeof(t_raycasting));
	pixel = -1;
	ray_angle = (double)(data->r.player.rotation_angle - (data->fov / 2));
	while (++pixel < data->num_rays)
	{
		ray_angle = normalize_angle(ray_angle);
		rays[pixel] = raycasting(data, ray_angle);
		ray_angle += (double)(data->fov / data->num_rays);
	}
	data->rays = rays;
}
