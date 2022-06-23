/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 17:58:28 by smodesto          #+#    #+#             */
/*   Updated: 2022/06/22 23:23:01 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#define mapWidth 25
#define mapHeight 25

int	wolrdmap[mapWidth][mapHeight]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

int	set_color(int wall, int side)
{
	int	color;

	color = WHITE;
	if (wall == 2)
		color = GREY;
	if (wall == 3)
		color = PURPLE;
	if (wall == 4)
		color = RED;
	if (side == 1)
		color = color / 2;
	return (color);
}

t_raycasting	go_through_ray(t_raycasting r)
{
	t_raycasting	new_r;
	t_bool			hit;

	hit = false;
	new_r = r;
	while (hit == false)
	{
		if (new_r.side_ds.x < new_r.side_ds.y)
		{
			new_r.side_ds.x += new_r.delta_ds.x;
			new_r.map.x += new_r.step.x;
			new_r.side = 0;
		}
		else
		{
			new_r.side_ds.y += new_r.delta_ds.y;
			new_r.map.y += new_r.step.y;
			new_r.side = 1;
		}
		if (wolrdmap[(int)new_r.map.x][(int)new_r.map.y] > 0)
			hit = true;
	}
	return (new_r);
}

void	dda(t_raycasting r, int x, t_image *img, int color)
{
	double		perpWall;
	int			lineHeight;
	int			start;
	int			end;

	if (r.side == 0)
		perpWall = r.side_ds.x - r.delta_ds.x;
	else
		perpWall = r.side_ds.y - r.delta_ds.y;
	lineHeight = (WIN_HEIGHT / perpWall);
	start = -lineHeight / 2 + WIN_HEIGHT / 2;
	if (start < 0)
		start = 0;
	end = lineHeight / 2 + WIN_HEIGHT / 2;
	if (end < 0)
		end = WIN_HEIGHT - 1;
	draw_vertical_line(img, x, start, end, color);
}

void	raycasting(t_image *img)
{
	t_raycasting	r;
	int				color;

	r.time = 0; r.old_time = 0;
	r.pos.x = 22; r.pos.y = 12;
	r.dir.x = -1; r.dir.y = 0;
	r.cam_plane.x = 0; r.cam_plane.y = 0.66;

	for (int pixel  = 0; pixel < WIN_WIDTH; pixel++)
	{
		r.ray = set_ray(r.dir, r.cam_plane, pixel);
		r.map.x = r.pos.x;
		r.map.y = r.pos.y;
		r.delta_ds = set_delta_ds(r.ray);
		r.step = set_step(r.ray);
		r.side_ds = set_side_ds(r.ray, r.map, r.pos, r.delta_ds);
		r = go_through_ray(r);
		color = set_color(wolrdmap[(int)r.map.x][(int)r.map.y], r.side);
		dda(r, pixel, img, color);
	}

}
