/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2D_to_3D.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 00:19:21 by smodesto          #+#    #+#             */
/*   Updated: 2022/07/17 18:06:27 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double	get_wall_strip_h(t_raycasting r, t_player p, int win_width)
{
	double	correct_wall_distance;
	double	distance_projection_plane;
	double	fov;

	fov = 60 * (M_PI / 180);
	correct_wall_distance = (r.distance * cos(r.ray_angle - p.rotation_angle));
	distance_projection_plane = (win_width / 2) / tan(fov / 2);
	return ((TILE_SIZE / correct_wall_distance) * distance_projection_plane);
}

void	render_walls(t_cub3d *data, t_point init, t_point end)
{
	int	pixel;
	int	wall_strip_h;
	int	color;

	pixel = -1;
	while (++pixel < data->num_rays)
	{
		color = DGREY;
		wall_strip_h = get_wall_strip_h(data->rays[pixel], data->r.player,
				data->win_width);
		init.y = -wall_strip_h / 2 + data->win_height / 2;
		if (init.y < 0)
			init.y = 0;
		end.y = wall_strip_h / 2 + data->win_height / 2;
		if (end.y >= data->win_height)
			end.y = data->win_height - 1;
		if (data->rays[pixel].hit_side == VERTICAL)
			color /= 2;
		init.x = pixel * WALL_STRIP_WIDTH;
		end.x = init.x + WALL_STRIP_WIDTH;
		draw_rectangle(data->img, color, init, end);
	}
}
