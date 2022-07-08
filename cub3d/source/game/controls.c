/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 11:21:03 by smodesto          #+#    #+#             */
/*   Updated: 2022/07/07 22:53:41 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	rotate_left(t_cub3d *data, t_raycasting r)
{
	data->r.player.rotation_angle += data->r.player.rotation_speed * LEFT;
/*	t_point	new_dir;
	t_point	new_plane;
	new_dir.x = r.dir.x * cos(r.player.rotation_speed) - r.dir.y
		* sin(r.player.rotation_speed);
	new_dir.y = r.dir.x * sin(r.player.rotation_speed) + r.dir.y
		* cos(r.player.rotation_speed);
	new_plane.x = r.cam_plane.x * cos(r.player.rotation_speed) - r.cam_plane.y
		* sin(r.player.rotation_speed);
	new_plane.y = r.cam_plane.x * sin(r.player.rotation_speed) + r.cam_plane.y
		* cos(r.player.rotation_speed);
	data->r.dir = new_dir;
	data->r.cam_plane = new_plane;*/
	draw_game(data, data->mlx, data->img);
}

void	rotate_right(t_cub3d *data, t_raycasting r)
{
	data->r.player.rotation_angle += data->r.player.rotation_speed * RIGHT;
/*	t_point	new_dir;
	t_point	new_plane;

	new_dir.x = r.dir.x * cos(-r.player.rotation_speed) - r.dir.y
		* sin(-r.player.rotation_speed);
	new_dir.y = r.dir.x * sin(-r.player.rotation_speed) + r.dir.y
		* cos(-r.player.rotation_speed);
	new_plane.x = r.cam_plane.x * cos(-r.player.rotation_speed) - r.cam_plane.y
		* sin(-r.player.rotation_speed);
	new_plane.y = r.cam_plane.x * sin(-r.player.rotation_speed) + r.cam_plane.y
		* cos(-r.player.rotation_speed);
	data->r.dir = new_dir;
	data->r.cam_plane = new_plane;*/
	draw_game(data, data->mlx, data->img);
}

void	move_forward(t_cub3d *data, t_raycasting r)
{
	t_point	new_pos;

	new_pos = r.player.pos;
	new_pos.x += cos(r.player.rotation_angle) * r.player.move_speed;
	new_pos.y += sin(r.player.rotation_angle) * r.player.move_speed;
	data->r.player.pos.x = new_pos.x;
	data->r.player.pos.y = new_pos.y;
	/*
		if (new_pos.y <= data->scene->map_height && new_pos.y > 0
		&& r.cub_map[(int)r.player.pos.x][(int)new_pos.y] == EMPTY)
		if (new_pos.x <= data->scene->map_width && new_pos.x > 0
		&& r.cub_map[(int)new_pos.x][(int)r.pos.y] == EMPTY)
	new_pos.x = data->r.player.pos.x;
	new_pos.y = data->r.player.pos.y;
	new_pos.x += r.dir.x * r.player.move_speed;
	new_pos.y += r.dir.y * r.player.move_speed;
	*/
	draw_game(data, data->mlx, data->img);
}

void	move_backward(t_cub3d *data, t_raycasting r)
{
	t_point	new_pos;

	new_pos = r.player.pos;
	new_pos.x -= cos(r.player.rotation_angle) * r.player.move_speed;
	new_pos.y -= sin(r.player.rotation_angle) * r.player.move_speed;
	data->r.player.pos.x = new_pos.x;
	data->r.player.pos.y = new_pos.y;
	/*
	new_pos.x = r.player.pos.x;
	new_pos.y = r.player.pos.y;
	new_pos.x -= r.dir.x * r.player.move_speed;
	new_pos.y -= r.dir.y * r.player.move_speed;
	if (new_pos.x <= data->scene->map_width && new_pos.x > 0
		&& r.cub_map[(int)new_pos.x][(int)r.pos.y] == EMPTY)
	if (new_pos.y <= data->scene->map_height && new_pos.y > 0
		&& r.cub_map[(int)r.player.pos.x][(int)new_pos.y] == EMPTY)
	*/
	draw_game(data, data->mlx, data->img);
}
