/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:20:56 by smodesto          #+#    #+#             */
/*   Updated: 2022/07/06 15:56:49 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	render_map(int **cub_map, int w, int h, t_image *img)
{
	t_render_map	m;

	m.iterator.y = 0;
	while (m.iterator.y < h)
	{
		m.iterator.x = 0;
		while (m.iterator.x < w)
		{
			m.tile.x = m.iterator.x * TILE_SIZE;
			m.tile.y = m.iterator.y * TILE_SIZE;
			if (cub_map[(int)m.iterator.y][(int)m.iterator.x] == 0)
				m.color = WHITE;
			else
				m.color = BLUE;
			m.tile_size.x = m.tile.x + TILE_SIZE;
			m.tile_size.y = m.tile.y + TILE_SIZE;
			draw_rectangle(img, m.color, m.tile, m.tile_size);
			draw_square(img, DGREY, m.tile, m.tile_size);
			m.iterator.x++;
		}
		m.iterator.y++;
	}
}

/*
	@brief: initialize all objects

void	setup()
{

}
*/
/*
	@brief: update all game objects before we render the next frame

void	update_minimap()
{

}
*/
/*
	@brief: render all objects frame by frame
*/
void	draw_minimap(t_cub3d *data, t_scene *scene, t_image *img)
{
	//update_minimap();
	render_map(scene->cub_map, scene->map_width, scene->map_height, img);
}
