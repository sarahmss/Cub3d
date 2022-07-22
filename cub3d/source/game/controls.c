/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 11:21:03 by smodesto          #+#    #+#             */
/*   Updated: 2022/07/21 21:57:59 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	rotate_left(t_cub3d *data)
{
	data->r.player.rotation_angle += data->r.player.rotation_speed * LEFT;
	draw_game(data, data->mlx, data->img);
}

void	rotate_right(t_cub3d *data)
{
	data->r.player.rotation_angle += data->r.player.rotation_speed * RIGHT;
	draw_game(data, data->mlx, data->img);
}

void	move_forward(t_cub3d *data, t_raycasting r)
{
	t_point	new_pos;
	t_point	map;
	t_point	next_step;

	new_pos = r.player.pos;
	new_pos.x += cos(r.player.rotation_angle) * r.player.move_speed;
	new_pos.y += sin(r.player.rotation_angle) * r.player.move_speed;
	map.x = new_pos.x / TILE_SIZE;
	map.y = new_pos.y / TILE_SIZE;
	next_step.x = (new_pos.x + cos(r.player.rotation_angle)
			* r.player.move_speed) / TILE_SIZE;
	next_step.y = (new_pos.y + sin(r.player.rotation_angle)
			* r.player.move_speed) / TILE_SIZE;
	if ((r.cub_map[(int)map.y][(int)map.x] != WALL)
		&& (r.cub_map[(int)next_step.y][(int)next_step.x] != WALL))
	{
		data->r.player.pos = new_pos;
		draw_game(data, data->mlx, data->img);
	}
}

void	move_backward(t_cub3d *data, t_raycasting r)
{
	t_point	new_pos;
	t_point	map;
	t_point	next_step;

	new_pos = r.player.pos;
	new_pos.x -= cos(r.player.rotation_angle) * r.player.move_speed;
	new_pos.y -= sin(r.player.rotation_angle) * r.player.move_speed;
	map.x = new_pos.x / TILE_SIZE;
	map.y = new_pos.y / TILE_SIZE;
	next_step.x = (new_pos.x - cos(r.player.rotation_angle)
			* r.player.move_speed) / TILE_SIZE;
	next_step.y = (new_pos.y - sin(r.player.rotation_angle)
			* r.player.move_speed) / TILE_SIZE;
	if ((r.cub_map[(int)map.y][(int)map.x] != WALL)
		&& (r.cub_map[(int)next_step.y][(int)next_step.x] != WALL))
	{
		data->r.player.pos = new_pos;
		draw_game(data, data->mlx, data->img);
	}
}
