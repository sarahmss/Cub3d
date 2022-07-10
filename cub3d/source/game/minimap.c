/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:20:56 by smodesto          #+#    #+#             */
/*   Updated: 2022/07/09 23:23:19 by smodesto         ###   ########.fr       */
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

/*
	draw player and dir in img
*/
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

void	render_rays(t_cub3d *data, t_player p)
{
	int		i;
	t_line	ray;

	i = 0;
	while (i < data->num_rays)
	{
		ray.x0 = p.pos.x;
		ray.y0 = p.pos.y;
		ray.x1 = data->rays[i].wall_hit.x;
		ray.y1 = data->rays[i].wall_hit.y;
		brasenham(ray, data->img, GREEN);
		i++;
	}
}

/*
	@brief: render all objects frame by frame
*/
void	draw_minimap(t_cub3d *data, t_scene *scene, t_image *img)
{
	render_map(scene->cub_map, scene->map_width, scene->map_height, img);
	render_player(data->r.player, img);
	render_rays(data, data->r.player);
}
