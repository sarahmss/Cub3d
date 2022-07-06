/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 00:12:12 by smodesto          #+#    #+#             */
/*   Updated: 2022/07/06 17:27:20 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
Defines direction in function of unitary vectors
		     N(0, -1)
                |
 EA(-1, 0)______|_____WE(1, 0)
			    |
			    |
		       S(0, 1)
*/
static t_point	get_direction(t_map direction)
{
	t_point	dir;

	if (direction == N)
	{
		dir.x = 0;
		dir.y = -1;
	}
	if (direction == S)
	{
		dir.x = 0;
		dir.y = 1;
	}
	if (direction == W)
	{
		dir.x = 1;
		dir.y = 0;
	}
	if (direction == E)
	{
		dir.x = -1;
		dir.y = 0;
	}
	return (dir);
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
				new_r.dir = get_direction(cub_map[i][j]);
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
		turn_direction: could be LEFT, RIGHT, STOP
		walk_direction: could be BACK, FRONT, STOP
		rotation_angle:
		move_speed:
		turn_speed:

*/
t_player	init_player(t_point pos)
{
	t_player	player;

	player.pos = pos;
	player.radius = 8;
	player.walk_direction = STOP;
	player.turn_direction = STOP;
	player.rotation_angle = M_PI / 2;
	player.move_speed = 5;
	player.rotation_speed = 3 * (M_PI / 180);
	return (player);
}

t_raycasting	define_points(t_scene *scn)
{
	t_raycasting	r;

	r = get_initial_position(scn->cub_map, scn->map_width, scn->map_height, r);
	r.cam_plane.x = 0;
	r.cam_plane.y = 0.66;
	r.cub_map = scn->cub_map;
	r.player = init_player(r.pos);
	return (r);
}
