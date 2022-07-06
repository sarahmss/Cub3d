/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 17:58:28 by smodesto          #+#    #+#             */
/*   Updated: 2022/07/06 15:57:16 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	set_color(t_side side)
{
	int	color;

	color = DGREY;
	if (side == VERTICAL)
		color = color / 2;
	return (color);
}

t_raycasting	go_through_ray(t_raycasting r)
{
	t_raycasting	new_r;
	t_bool			hit;

	hit = false;
	new_r = r;
	while (hit == false)
	{
		if (new_r.side_ds.x < new_r.side_ds.y)
		{
			new_r.side_ds.x += new_r.delta_ds.x;
			new_r.map.x += new_r.step.x;
			new_r.side = HORIZONTAL;
		}
		else
		{
			new_r.side_ds.y += new_r.delta_ds.y;
			new_r.map.y += new_r.step.y;
			new_r.side = VERTICAL;
		}
		if (r.cub_map[(int)new_r.map.x][(int)new_r.map.y] > 0)
			hit = true;
	}
	return (new_r);
}

/*
	substituir draw vertical line to put sprite to window
*/
void	dda(t_raycasting r, int x, t_image *img, int color)
{
	double		perp_wall;
	int			line_height;
	t_point		start_end;

	if (r.side == HORIZONTAL)
		perp_wall = r.side_ds.x - r.delta_ds.x;
	else
		perp_wall = r.side_ds.y - r.delta_ds.y;
	line_height = (int)(WIN_HEIGHT / perp_wall);
	start_end.x = (-line_height / 2) + (WIN_HEIGHT / 2);
	if (start_end.x < 0)
		start_end.x = 0;
	start_end.y = (line_height / 2) + (WIN_HEIGHT / 2);
	if (start_end.y >= WIN_HEIGHT)
		start_end.y = WIN_HEIGHT - 1;
	draw_vertical_line(img, x, start_end, color);
}

void	raycasting(t_image *img, t_cub3d *data)
{
	t_raycasting	r;
	static int		init;
	int				pixel;

	if (init++ == 0)
	{
		r = define_points(data->scene);
		data->r = r;
	}
	else
		r = data->r;
	pixel = -1;
	while (pixel++ < WIN_WIDTH)
	{
		r.ray = set_ray(r.dir, r.cam_plane, pixel);
		r.map.x = r.pos.x;
		r.map.y = r.pos.y;
		r.delta_ds = set_delta_ds(r.ray);
		r.step = set_step(r.ray);
		r.side_ds = set_side_ds(r.ray, r.map, r.pos, r.delta_ds);
		r = go_through_ray(r);
		dda(r, pixel, img, set_color(r.side));
	}
}
