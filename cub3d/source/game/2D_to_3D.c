/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2D_to_3D.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 00:19:21 by smodesto          #+#    #+#             */
/*   Updated: 2022/08/22 16:07:36 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	get_color(t_stripe s, int y)
{
	t_textures		facing_side;
	int				distance_from_top;
	double			height_scale;

	facing_side = get_facing_side(s.ray.ray_angle, s.ray.hit_side);
	distance_from_top = y + (s.height / 2) - (s.data->win_height / 2);
	height_scale = s.data->textures[facing_side]->height / s.height;
	s.offset.x = get_x_offset(s.ray, s.data->textures[facing_side]->width);
	s.offset.y = distance_from_top * height_scale;
	s.color = get_wall_pixel_color(s.data->textures[facing_side],
			s.offset.x, s.offset.y);
	if (s.ray.hit_side == VERTICAL)
		s.color = change_color_intensity(s.color, 0.5);
	return (s.color);
}

void	draw_textured_rectangle(t_stripe s)
{
	t_line	vector;

	vector.y0 = s.init.y;
	while (vector.y0 < s.end.y)
	{
		s.color = get_color(s, vector.y0 - 1);
		vector.x0 = s.init.x;
		while (vector.x0 < s.end.x)
		{
			if (vector.x0 < s.end.x - 1)
			{
				vector.x1 = vector.x0 + 1;
				vector.y1 = vector.y0;
				brasenham(vector, s.data->img, s.color);
			}
			if (vector.y0 < s.end.y - 1)
			{
				vector.x1 = vector.x0;
				vector.y1 = vector.y0 + 1;
				brasenham(vector, s.data->img, s.color);
			}
			vector.x0++;
		}
		vector.y0++;
	}
}

double	get_height(t_raycasting r, t_player p, int win_width, double fov)
{
	double	correct_wall_distance;
	double	distance_projection_plane;

	correct_wall_distance = (r.distance * cos(r.ray_angle - p.rotation_angle));
	distance_projection_plane = (win_width / 2) / tan(fov / 2);
	return ((TILE_SIZE / correct_wall_distance) * distance_projection_plane);
}

static void	draw_background(t_cub3d *data, t_stripe s)
{
	t_point	init;
	t_point	end;

	init.x = s.init.x;
	end.x = s.end.x;
	init.y = -1;
	end.y = s.init.y;
	draw_rectangle(data->img, data->scene->ceil, init, end);
	init.y = s.end.y;
	end.y = data->win_height;
	draw_rectangle(data->img, data->scene->floor, init, end);
}

void	render_walls(t_cub3d *data, t_point win)
{
	int			x;
	t_stripe	s;

	x = -1;
	s.data = data;
	while (++x < data->num_rays)
	{
		s.ray = data->rays[x];
		s.height = get_height(s.ray, data->r.player, win.x,
				data->fov);
		s.init.y = -(s.height / 2) + (win.y / 2);
		if (s.init.y < 0)
			s.init.y = 0;
		s.end.y = (s.height / 2) + (win.y / 2);
		if (s.end.y >= win.y)
			s.end.y = win.y - 1;
		s.init.x = x * WALL_STRIP_WIDTH;
		s.end.x = s.init.x + WALL_STRIP_WIDTH;
		draw_textured_rectangle(s);
		draw_background(data, s);
	}
}
