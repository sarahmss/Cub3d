/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 00:12:12 by smodesto          #+#    #+#             */
/*   Updated: 2022/08/16 22:07:36 by smodesto         ###   ########.fr       */
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
		return ((3 * M_PI) / 2);
	if (direction == S)
		return (M_PI / 2);
	if (direction == W)
		return (0);
	if (direction == E)
		return (M_PI);
	return (0);
}

static t_point	get_initial_position(int **cub_map, int width, int height)
{
	int		i;
	int		j;
	t_point	pos;

	i = 0;
	pos.x = 0;
	pos.y = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (cub_map[i][j] == N || cub_map[i][j] == S
				|| cub_map[i][j] == W || cub_map[i][j] == E)
			{
				pos.x = j * TILE_SIZE;
				pos.y = i * TILE_SIZE;
				return (pos);
			}
			j++;
		}
		i++;
	}
	return (pos);
}

/*
	@brief: Init player paramaters
		pos: initial position;
		radius: in pixels
		rotation_angle:
		move_speed:
		turn_speed:

*/
t_player	init_player(int **cub_map, int width, int height)
{
	t_player	player;

	player.pos = get_initial_position(cub_map, width, height);
	player.rotation_angle = get_direction(cub_map
		[(int)(player.pos.y / TILE_SIZE)][(int)(player.pos.x / TILE_SIZE)]);
	player.radius = 8;
	player.move_speed = 2.0;
	player.rotation_speed = 2 * (M_PI / 180);
	return (player);
}

t_raycasting	define_points(t_scene *scn)
{
	t_raycasting	r;

	r.cub_map = scn->cub_map;
	r.player = init_player(scn->cub_map, scn->map_width, scn->map_height);
	r.wall_hit.x = 0;
	r.wall_hit.y = 0;
	r.distance = 0;
	r.hit_side = HORIZONTAL;
	return (r);
}
