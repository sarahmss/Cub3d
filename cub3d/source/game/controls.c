/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 11:21:03 by smodesto          #+#    #+#             */
/*   Updated: 2022/08/17 23:13:55 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	move_forward(t_cub3d *data, t_raycasting r)
{
	t_point	new_pos;
	t_point	map;
	t_point	next_step;

	new_pos = r.player.pos;
	new_pos.x += cos(r.player.rotation_angle) * r.player.move_speed;
	new_pos.y += sin(r.player.rotation_angle) * r.player.move_speed;
	map.x = (new_pos.x / TILE_SIZE);
	map.y = (new_pos.y / TILE_SIZE);
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

void	move_left(t_cub3d *data, t_raycasting r, int key)
{
	t_point	new_pos;
	t_point	map;
	t_point	next_step;

	if ((!is_ray_facing_left(r.ray_angle) && !is_ray_facing_right(r.ray_angle))
		&& (key == MAIN_KEY_A))
		return (move_right(data, r, key));
	new_pos = r.player.pos;
	new_pos.x -= sin(r.player.rotation_angle) * r.player.move_speed;
	new_pos.y -= cos(r.player.rotation_angle) * r.player.move_speed;
	map.x = new_pos.x / TILE_SIZE;
	map.y = new_pos.y / TILE_SIZE;
	next_step.x = (new_pos.x - sin(r.player.rotation_angle)
			* r.player.move_speed) / TILE_SIZE;
	next_step.y = (new_pos.y - cos(r.player.rotation_angle)
			* r.player.move_speed) / TILE_SIZE;
	if ((r.cub_map[(int)map.y][(int)map.x] != WALL)
		&& (r.cub_map[(int)next_step.y][(int)next_step.x] != WALL))
	{
		data->r.player.pos = new_pos;
		draw_game(data, data->mlx, data->img);
	}
}

void	move_right(t_cub3d *data, t_raycasting r, int key)
{
	t_point	new_pos;
	t_point	map;
	t_point	next_step;

	if ((!is_ray_facing_left(r.ray_angle) && !is_ray_facing_right(r.ray_angle))
		&& (key == MAIN_KEY_D))
		return (move_left(data, r, key));
	new_pos = r.player.pos;
	new_pos.x += sin(r.player.rotation_angle) * r.player.move_speed;
	new_pos.y += cos(r.player.rotation_angle) * r.player.move_speed;
	map.x = new_pos.x / TILE_SIZE;
	map.y = new_pos.y / TILE_SIZE;
	next_step.x = (new_pos.x + sin(r.player.rotation_angle)
			* r.player.move_speed) / TILE_SIZE;
	next_step.y = (new_pos.y + cos(r.player.rotation_angle)
			* r.player.move_speed) / TILE_SIZE;
	if ((r.cub_map[(int)map.y][(int)map.x] != WALL)
		&& (r.cub_map[(int)next_step.y][(int)next_step.x] != WALL))
	{
		data->r.player.pos = new_pos;
		draw_game(data, data->mlx, data->img);
	}
}
