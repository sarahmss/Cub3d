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

void	render_walls(t_cub3d *data, t_point init, t_point end, t_point win)
{
	int	x;
	int	height;
	int	color;

	x = -1;
	while (++x < data->num_rays)
	{
		color = DGREY;
		height = get_height(data->rays[x], data->r.player, win.x,
				data->fov);
		init.y = -height / 2 + win.y / 2;
		if (init.y < 0)
			init.y = 0;
		end.y = height / 2 + win.y / 2;
		if (end.y >= win.y)
			end.y = win.y - 1;
		if (data->rays[x].hit_side == VERTICAL)
			color /= 2;
		init.x = x * WALL_STRIP_WIDTH;
		end.x = init.x + WALL_STRIP_WIDTH;
		draw_rectangle(data->img, color, init, end);
	}
}
