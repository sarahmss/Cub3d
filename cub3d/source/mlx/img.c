/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 17:15:21 by smodesto          #+#    #+#             */
/*   Updated: 2022/06/22 23:22:55 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
	Put pixel in img address in x and y positions
*/
void	my_mlx_pixel_put(int x, int y, t_image *img, int color)
{
	int	i;

	if ((x < 0) || (x >= WIN_WIDTH) || (y < 0) || (y >= WIN_HEIGHT))
		return ;
	i = (y * img->line_size) + (x * (img->bpp / 8));
	*(unsigned int *)&img->data_address[i] = color;
}

/*
	Fill background with especific colors
*/
void	background(t_image *img)
{
	int	*image;
	int	i;

	ft_bzero(img->data_address, WIN_WIDTH * WIN_HEIGHT * (img->bpp / 8));
	image = (int *)(img->data_address);
	i = 0;
	while (i < WIN_HEIGHT * WIN_WIDTH)
	{
		if (i < (WIN_HEIGHT * WIN_WIDTH / 2))
			image[i] = WHITE;
		else
			image[i] = GREEN;
		i++;
	}
}

/*
	Create an image and calls draw function to draw into it
*/
void	ft_create_image(t_mlx *mlx, t_image *img)
{
	if (img->img != NULL)
		mlx_destroy_image(mlx->mlx, img->img);
	if (mlx->win)
		mlx_clear_window(mlx->mlx, mlx->win);
	img->img = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	img->data_address = mlx_get_data_addr(img->img, &(img->bpp),
			&(img->line_size), &(img->endian));
	background(img);
	raycasting(img);
	mlx_put_image_to_window(mlx->mlx, mlx->win, img->img, 0, 0);
}
