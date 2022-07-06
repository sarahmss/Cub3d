/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 19:58:01 by smodesto          #+#    #+#             */
/*   Updated: 2022/07/06 17:25:44 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_circle(t_point center, int color, int radius, t_image *img)
{
	int	radius_squared;
	int	x;
	int	y;

	radius_squared = pow(radius, 2);
	x = center.x - radius;
	y = center.y - radius;
	while (y <= center.y + radius)
	{
		while (x <= center.x + radius)
		{
			if ((pow(x - center.x, 2) + pow(y - center.y, 2)) <= radius_squared)
				my_mlx_pixel_put(x, y, img, color);
			x++;
		}
		y++;
		x = center.x - radius;
	}
}

/*
	@brief: given begin and end draw a vertical line at column x
	@param: begin_end: put the coordinates of yi at begin_end.x and yf at
	 begin_end.y
*/
void	draw_vertical_line(t_image *img, int x, t_point begin_end, int color)
{
	t_line	vector;

	vector.y0 = begin_end.x;
	vector.x0 = x;
	vector.x1 = x;
	while (vector.y0 < begin_end.y)
	{
		vector.y1 = vector.y0 + 1;
		brasenham(vector, img, color);
		vector.y0++;
	}
}

/*
	@brief: given begin and end draw a horizontal line at line y
	@param: begin_end: put the coordinates of xi at begin_end.x and xf at
	 begin_end.y
*/
void	draw_horizontal_line(t_image *img, int y, t_point begin_end, int color)
{
	t_line	vector;

	vector.x0 = begin_end.x;
	vector.y0 = y;
	vector.y1 = y;
	while (vector.x0 < begin_end.y)
	{
		vector.x1 = vector.x0 + 1;
		brasenham(vector, img, color);
		vector.x0++;
	}
}

void	draw_rectangle(t_image *img, int color, t_point init, t_point end)
{
	t_line	vector;

	vector.y0 = init.y;
	while (vector.y0 < end.y)
	{
		vector.x0 = init.x;
		while (vector.x0 < end.x)
		{
			if (vector.x0 < end.x - 1)
			{
				vector.x1 = vector.x0 + 1;
				vector.y1 = vector.y0;
				brasenham(vector, img, color);
			}
			if (vector.y0 < end.y - 1)
			{
				vector.x1 = vector.x0;
				vector.y1 = vector.y0 + 1;
				brasenham(vector, img, color);
			}
			vector.x0++;
		}
		vector.y0++;
	}
}

void	draw_square(t_image *img, int color, t_point init, t_point end)
{
	t_point	begin_end;

	begin_end.x = init.x;
	begin_end.y = end.x;
	draw_horizontal_line(img, init.y, begin_end, color);
	draw_horizontal_line(img, end.y, begin_end, color);
	begin_end.x = init.y;
	begin_end.y = end.y;
	draw_vertical_line(img, init.x, begin_end, color);
	draw_vertical_line(img, end.x, begin_end, color);
}
