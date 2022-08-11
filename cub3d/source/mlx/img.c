/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 17:15:21 by smodesto          #+#    #+#             */
/*   Updated: 2022/07/28 22:06:19 by smodesto         ###   ########.fr       */
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
	Put pixel in img address in x and y positions
*/
void	my_mlx_pixel_put(int x, int y, t_image *img, int color)
{
	int	i;

	if ((x < 0) || (x >= img->width) || (y < 0) || (y >= img->height))
		return ;
	i = (y * img->line_size) + (x * (img->bpp / 8));
	*(unsigned int *)&img->data_address[i] = color;
}

/*
	Create an image and calls draw function to draw into it
*/
void	ft_create_image(t_mlx *mlx, t_image *img, int width, int height)
{
	if (img->img != NULL)
		mlx_destroy_image(mlx->mlx, img->img);
	img->img = mlx_new_image(mlx->mlx, width, height);
	img->data_address = mlx_get_data_addr(img->img, &(img->bpp),
			&(img->line_size), &(img->endian));
}
