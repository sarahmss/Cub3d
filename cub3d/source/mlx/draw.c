/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 19:58:01 by smodesto          #+#    #+#             */
/*   Updated: 2022/07/06 14:05:28 by smodesto         ###   ########.fr       */
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

void	draw_game(t_cub3d *data, t_mlx *mlx, t_image *img)
{
	ft_create_image(mlx, img);
	background(img, data->scene->floor_color, data->scene->ceiling_color);
	raycasting(img, data);
	mlx_put_image_to_window(mlx->mlx, mlx->win, img->img, 0, 0);
}
