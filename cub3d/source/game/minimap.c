/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:20:56 by smodesto          #+#    #+#             */
/*   Updated: 2022/07/06 18:00:40 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
	@brief: draw_map in img;
*/
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

void	render_player(t_player player, t_image *img)
{
	t_line	line;

	line.x0 = player.pos.x;
	line.y0 = player.pos.y;
	line.x1 = player.pos.x + cos(player.rotation_angle) * 30;
	line.y1 = player.pos.y + sin(player.rotation_angle) * 30;
	draw_circle(player.pos, RED, player.radius, img);
	brasenham(line, img, RED);
}

/*
	update player position based on turn_direction and walk_direction

t_player	update_player(t_cub3d *data)
{

}
*/
/*
	@brief: update all game objects before we render the next frame

void	update_minimap(t_cub3d *data)
{
	data->r.player = update_player(data);
}
*
/*
	@brief: render all objects frame by frame
*/
void	draw_minimap(t_cub3d *data, t_scene *scene, t_image *img)
{
	data->r = define_points(data->scene);
	//update_minimap();
	render_map(scene->cub_map, scene->map_width, scene->map_height, img);
	render_player(data->r.player, img);
}
