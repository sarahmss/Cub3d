/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2D_to_3D.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 00:19:21 by smodesto          #+#    #+#             */
/*   Updated: 2022/07/29 00:09:36 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double	get_height(t_raycasting r, t_player p, int win_width, double fov)
{
	double	correct_wall_distance;
	double	distance_projection_plane;

	correct_wall_distance = (r.distance * cos(r.ray_angle - p.rotation_angle));
	distance_projection_plane = (win_width / 2) / tan(fov / 2);
	return ((TILE_SIZE / correct_wall_distance) * distance_projection_plane);
}

int    change_color_intensity(int color, float factor)
{
    int    r;
    int    g;
    int    b;

    r = (color & 0xFF0000) * factor;
    g = (color & 0x00FF00) * factor;
    b = (color & 0x0000FF) * factor;
    return((r & 0xFF0000) | (g & 0x00FF00) | (b & 0x0000FF));
}

void render_slices(int x, t_wall w, t_cub3d *data)
{
		int 	y;
		int 	t_num;
		double	height_scale;
		double	color_factor;
		int i; 

		y = w.top_y - 1;
		while(++y < w.bottom_y)
		{
			t_num = get_facing_side(data->rays[x].ray_angle, data->rays[x].hit_side);
			w.distance_top = y + (w.height / 2) - (data->win_height / 2);
			height_scale = data->textures[t_num]->height / w.height;
			w.offset.y = w.distance_top * height_scale;
			w.pixel_color = get_wall_pixel_color(data->textures[t_num], w.offset.x, w.offset.y);
			if (data->rays[x].hit_side == VERTICAL)
				w.pixel_color = change_color_intensity(w.pixel_color, 1);
			i = -1;
			while (++i < WALL_STRIP_WIDTH)
				my_mlx_pixel_put(x + i, y, data->img, w.pixel_color);	
			//my_mlx_pixel_put(x, y, data->img, w.pixel_color);
			
		}
}

void	render_walls(t_cub3d *data, t_point win)
{
	int	x;
	int	height;
	int	color;
	t_wall w;

	x = -1;
	printf("%d\n", data->num_rays);
	while (++x < data->num_rays)
	{
		color = DGREY;
		w.height = get_height(data->rays[x], data->r.player, win.x,
				data->fov);
		w.top_y = -(w.height / 2) + (win.y / 2);
		if (w.top_y < 0)
			w.top_y = 0;
		if (w.top_y >= win.y)
			w.top_y = win.y;
		w.bottom_y = (height / 2) + (win.y / 2);
		if (w.bottom_y < 0)
			w.bottom_y = 0;
		if (w.bottom_y >= win.y)
			w.bottom_y = win.y;
		w.offset.x = get_x_offset(data->rays[x]);
		render_slices(x, w, data);
	}
}
