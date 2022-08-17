/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 17:58:28 by smodesto          #+#    #+#             */
/*   Updated: 2022/08/17 19:26:47 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_point	hit(t_raycasting *r, t_side s, t_point win, double ray_angle)
{
	t_point			next_touch;
	t_point			map;

	r->ray_angle = ray_angle;
	r->intercept = set_intercept(r->ray_angle, r->player.pos, s);
	r->step = set_step(r->ray_angle, s);
	r->hit_side = s;
	next_touch = r->intercept;
	while ((next_touch.x >= 0 && next_touch.x <= win.x)
		&& (next_touch.y >= 0 && next_touch.y <= win.y))
	{
		map = set_map(r->ray_angle, next_touch, s, win);
		if (r->cub_map[(int)map.y][(int)map.x] == WALL)
			return (next_touch);
		next_touch.x += r->step.x;
		next_touch.y += r->step.y;
	}
	return (next_touch);
}

t_raycasting	raycasting(t_cub3d *data, double ray_angle, t_point win)
{
	t_raycasting	r_h;
	t_raycasting	r_v;

	r_h = data->r;
	r_v = data->r;
	r_h.wall_hit = hit(&r_h, HORIZONTAL, win, ray_angle);
	r_v.wall_hit = hit(&r_v, VERTICAL, win, ray_angle);
	r_h.distance = distance_between_points(r_h.player.pos, r_h.wall_hit);
	r_v.distance = distance_between_points(r_v.player.pos, r_v.wall_hit);
	if (r_h.distance < r_v.distance)
		return (r_h);
	return (r_v);
}

void	cast_all_rays(t_cub3d *data, t_point win)
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
		rays[pixel] = raycasting(data, ray_angle, win);
		ray_angle += (double)(data->fov / data->num_rays);
	}
	data->rays = rays;
}
