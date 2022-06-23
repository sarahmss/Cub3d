/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 00:12:12 by smodesto          #+#    #+#             */
/*   Updated: 2022/06/23 01:28:46 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_point	get_initial_position(int **cub_map, int width, int height)
{
	int		i;
	int		j;
	t_point	initial_pos;

	i = 0;
	initial_pos.x = 0;
	initial_pos.y = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (cub_map[i][j] == N || cub_map[i][j] == S
				|| cub_map[i][j] == W || cub_map[i][j] == E)
			{
				initial_pos.x = j;
				initial_pos.y = i;
				return (initial_pos);
			}
			j++;
		}
		i++;
	}
	return (initial_pos);
}

t_raycasting	define_points(t_scene *scn)
{
	t_raycasting	r;

	r.time = 0;
	r.old_time = 0;
	r.dir.x = -1;
	r.dir.y = 0;
	r.cam_plane.x = 0;
	r.cam_plane.y = 0.66;
	r.pos = get_initial_position(scn->cub_map, scn->map_width, scn->map_height);
//	r.pos.x = 22;
//	r.pos.y = 12;
	return (r);
}
