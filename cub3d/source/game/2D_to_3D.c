/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2D_to_3D.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 00:19:21 by smodesto          #+#    #+#             */
/*   Updated: 2022/08/15 20:02:52 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*

*/
int	get_color(t_stripe s, int y)
{
	t_side			facing_side;
	int				distance_from_top;
	int				height_scale;

	facing_side = get_facing_side(s.ray.ray_angle, s.ray.hit_side);
	distance_from_top = y + (s.height / 2) - (s.data->win_height / 2);
	height_scale = s.data->textures[facing_side]->height / s.height;
	s.offset.y = distance_from_top * height_scale;
	s.color = get_wall_pixel_color(s.data->textures[facing_side], s.offset.x, s.offset.y);
	return (s.color);
}

static void	textured_brasenham(t_line line, t_image *img, t_stripe s)
{
	t_line	*temp;

	temp = &line;
	temp->delta_x = (temp->x1 - temp->x0);
	temp->delta_y = (temp->y1 - temp->y0);
	temp->max = max(mod(temp->delta_x), mod(temp->delta_y));
	temp->delta_x /= temp->max;
	temp->delta_y /= temp->max;
	s.offset.x = get_x_offset(s.ray);
	while ((int)(temp->x0 - temp->x1) || (int)(temp->y0 - temp->y1))
	{
		s.color = get_color(s, s.init.y - 1);
		my_mlx_pixel_put(temp->x0, temp->y0, img, s.color);
		temp->x0 += temp->delta_x;
		temp->y0 += temp->delta_y;
	}
}

void	draw_textured_rectangle(t_stripe s)
{
	t_line	vector;

	vector.y0 = s.init.y;
	while (vector.y0 < s.end.y)
	{
		vector.x0 = s.init.x;
		while (vector.x0 < s.end.x)
		{
			if (vector.x0 < s.end.x - 1)
			{
				vector.x1 = vector.x0 + 1;
				vector.y1 = vector.y0;
				textured_brasenham(vector, s.data->img, s);
			}
			if (vector.y0 < s.end.y - 1)
			{
				vector.x1 = vector.x0;
				vector.y1 = vector.y0 + 1;
				textured_brasenham(vector, s.data->img, s);
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
	}
}
