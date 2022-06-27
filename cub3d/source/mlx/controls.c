/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 11:21:03 by smodesto          #+#    #+#             */
/*   Updated: 2022/06/27 12:12:52 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


void	rotate_left(t_cub3d *data, t_raycasting r)
{
	t_point	new_dir;
	t_point	new_plane;

	new_dir.x = r.dir.x * cos(r.turn_speed) - r.dir.y * sin(r.turn_speed);
	new_dir.y = r.dir.x * sin(r.turn_speed) + r.dir.y * cos(r.turn_speed);
	new_plane.x = r.cam_plane.x * cos(r.turn_speed) - r.cam_plane.y * sin(r.turn_speed);
	new_plane.y = r.cam_plane.x * sin(r.turn_speed) + r.cam_plane.y * cos(r.turn_speed);
	data->r.dir = new_dir;
	data->r.cam_plane = new_plane;
	ft_create_image(data->mlx, data->img, data);
}

void	rotate_right(t_cub3d *data, t_raycasting r)
{
	t_point	new_dir;
	t_point	new_plane;

	new_dir.x = r.dir.x * cos(-r.turn_speed) - r.dir.y * sin(-r.turn_speed);
	new_dir.y = r.dir.x * sin(-r.turn_speed) + r.dir.y * cos(-r.turn_speed);
	new_plane.x = r.cam_plane.x * cos(-r.turn_speed) - r.cam_plane.y * sin(-r.turn_speed);
	new_plane.y = r.cam_plane.x * sin(-r.turn_speed) + r.cam_plane.y * cos(-r.turn_speed);
	data->r.dir = new_dir;
	data->r.cam_plane = new_plane;
	ft_create_image(data->mlx, data->img, data);
}


void	move_forward(t_cub3d *data, t_raycasting r)
{
	t_point	new_pos;

	new_pos.x = r.pos.x + r.dir.x * r.move_speed;
	new_pos.y = r.pos.y + r.dir.y * r.move_speed;

	if (r.cub_map[(int)new_pos.x][(int)r.pos.y] == EMPTY)
		data->r.pos.x = new_pos.x;
	if (r.cub_map[(int)r.pos.x][(int)new_pos.y] == EMPTY)
		data->r.pos.y = new_pos.y;
	ft_create_image(data->mlx, data->img, data);
}

void	move_backward(t_cub3d *data, t_raycasting r)
{
	t_point	new_pos;

	new_pos.x = r.pos.x - r.dir.x * r.move_speed;
	new_pos.y = r.pos.y - r.dir.y * r.move_speed;

	if (new_pos.x <= data->scene->map_width
			&& r.cub_map[(int)new_pos.x][(int)r.pos.y] == EMPTY)
		data->r.pos.x = new_pos.x;
	if (new_pos.y <= data->scene->map_height
			&& r.cub_map[(int)r.pos.x][(int)new_pos.y] == EMPTY)
		data->r.pos.y = new_pos.y;
	ft_create_image(data->mlx, data->img, data);
}
