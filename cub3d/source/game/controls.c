/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 11:21:03 by smodesto          #+#    #+#             */
/*   Updated: 2022/07/07 23:25:28 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	rotate_left(t_cub3d *data, t_raycasting r)
{
	data->r.player.rotation_angle += data->r.player.rotation_speed * LEFT;
	draw_game(data, data->mlx, data->img);
}

void	rotate_right(t_cub3d *data, t_raycasting r)
{
	data->r.player.rotation_angle += data->r.player.rotation_speed * RIGHT;
	draw_game(data, data->mlx, data->img);
}

void	move_forward(t_cub3d *data, t_raycasting r)
{
	t_point	new_pos;

	new_pos = r.player.pos;
	new_pos.x += cos(r.player.rotation_angle) * r.player.move_speed;
	new_pos.y += sin(r.player.rotation_angle) * r.player.move_speed;
	if (r.cub_map[(int)new_pos.x / TILE_SIZE][(int)new_pos.y / TILE_SIZE]
	== EMPTY)
		data->r.player.pos = new_pos;
	if (new_pos.x == data->r.player.pos.x || new_pos.x == data->r.player.pos.x)
		draw_game(data, data->mlx, data->img);
}

void	move_backward(t_cub3d *data, t_raycasting r)
{
	t_point	new_pos;

	new_pos = r.player.pos;
	new_pos.x -= cos(r.player.rotation_angle) * r.player.move_speed;
	new_pos.y -= sin(r.player.rotation_angle) * r.player.move_speed;
	if (r.cub_map[(int)new_pos.x / TILE_SIZE][(int)new_pos.y / TILE_SIZE]
	== EMPTY)
		data->r.player.pos = new_pos;
	if (new_pos.x == data->r.player.pos.x || new_pos.x == data->r.player.pos.x)
		draw_game(data, data->mlx, data->img);
}
