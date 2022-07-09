/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 00:12:12 by smodesto          #+#    #+#             */
/*   Updated: 2022/07/09 20:20:05 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
Defines direction in function of unitary vectors
		     N 3pi / 2
                |
 EA pi______|_____WE 0
			    |
			    |
		       S pi/2
*/
static double	get_direction(t_map direction)
{
	if (direction == N)
		return (3 * M_PI / 2);
	if (direction == S)
		return (M_PI / 2);
	if (direction == W)
		return (0);
	if (direction == E)
		return (M_PI);
	return (0);
}

static t_raycasting	get_initial_position(int **cub_map, int width, int height,
t_raycasting r)
{
	int				i;
	int				j;
	t_raycasting	new_r;

	i = 0;
	new_r = r;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (cub_map[i][j] == N || cub_map[i][j] == S
				|| cub_map[i][j] == W || cub_map[i][j] == E)
			{
				new_r.pos.x = j * TILE_SIZE;
				new_r.pos.y = i * TILE_SIZE;
				return (new_r);
			}
			j++;
		}
		i++;
	}
	return (new_r);
}

/*
	@brief: Init player paramaters
		pos: initial position;
		radius: in pixels
		rotation_angle:
		move_speed:
		turn_speed:

*/
t_player	init_player(t_point pos, t_map direction)
{
	t_player	player;

	player.pos = pos;
	player.radius = 8;
	player.rotation_angle = get_direction(direction);
	player.move_speed = 2.0;
	player.rotation_speed = 2 * (M_PI / 180);
	return (player);
}

t_raycasting	define_points(t_scene *scn)
{
	t_raycasting	r;

	r = get_initial_position(scn->cub_map, scn->map_width, scn->map_height, r);
	r.cam_plane.x = 0;
	r.cam_plane.y = 0.66;
	r.dir.x = 0;
	r.dir.y = -1;
	r.cub_map = scn->cub_map;
	r.player = init_player(r.pos, r.cub_map[(int)r.pos.y / TILE_SIZE]
		[(int)r.pos.x / TILE_SIZE]);
	return (r);
}
