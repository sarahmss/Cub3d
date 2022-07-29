/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rgbhex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:50:44 by smodesto          #+#    #+#             */
/*   Updated: 2022/07/28 21:35:59 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
	Fill background with especific colors
	f and c: array with RGB color
	wh: wh.x win width; wh.y win height
*/
void	background(t_image *img, int f[3], int c[3], t_point wh)
{
	int	*image;
	int	i;

	ft_bzero(img->data_address, wh.x * wh.y * (img->bpp / 8));
	image = (int *)(img->data_address);
	i = 0;
	while (i < wh.x * wh.y)
	{
		if (i < (wh.x * wh.y / 2))
			image[i] = ft_rgbhex(f[0], f[1], f[2]);
		else
			image[i] = ft_rgbhex(c[0], c[1], c[2]);
		i++;
	}
}

static char	get_hex(float num)
{
	if ((int)num == 0)
		return ('0');
	if (num <= 9)
		return (num + '0');
	if (num == 10)
		return ('A');
	if (num == 11)
		return ('B');
	if (num == 12)
		return ('C');
	if (num == 13)
		return ('D');
	return ('E');
}

int	ft_rgbhex(int r, int g, int b)
{
	char	str_hex[6];

	str_hex[0] = get_hex(r / 16);
	str_hex[1] = get_hex(fmod(r, 16));
	str_hex[2] = get_hex(g / 16);
	str_hex[3] = get_hex(fmod(g, 16));
	str_hex[4] = get_hex(b / 16);
	str_hex[5] = get_hex(fmod(b, 16));
	str_hex[6] = '\0';
	return (ft_atoi_base(str_hex, "0123456789ABCDEF"));
}
