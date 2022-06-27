/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morgana <morgana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 19:58:01 by smodesto          #+#    #+#             */
/*   Updated: 2022/06/23 20:16:35 by morgana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
	Brasenham's algorithme draws lines between two points
*/
void	brasenham(t_line line, t_image *img, int color)
{
	t_line	*temp;

	temp = &line;
	temp->delta_x = (temp->x1 - temp->x0);
	temp->delta_y = (temp->y1 - temp->y0);
	temp->max = max(mod(temp->delta_x), mod(temp->delta_y));
	temp->delta_x /= temp->max;
	temp->delta_y /= temp->max;
	while ((int)(temp->x0 - temp->x1) || (int)(temp->y0 - temp->y1))
	{
		my_mlx_pixel_put(temp->x0, temp->y0, img, color);
		temp->x0 += temp->delta_x;
		temp->y0 += temp->delta_y;
	}
}

/*
	given begin and end draw a vertical line at column x
*/
void	draw_vertical_line(t_image *img, int x, int begin, int end, int color)
{
	t_line	vector;

	vector.y0 = begin;
	vector.x0 = x;
	vector.x1 = x;
	while (vector.y0 < end)
	{
		vector.y1 = vector.y0 + 1;
		brasenham(vector, img, color);
		vector.y0++;
	}
}
