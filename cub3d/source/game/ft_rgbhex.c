/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rgbhex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:50:44 by smodesto          #+#    #+#             */
/*   Updated: 2022/08/22 17:49:20 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	change_color_intensity(int color, float factor)
{
	int	r;
	int	g;
	int	b;

	r = (color & 0xFF0000) * factor;
	g = (color & 0x00FF00) * factor;
	b = (color & 0x0000FF) * factor;
	return ((r & 0xFF0000) | (g & 0x00FF00) | (b & 0x0000FF));
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
	char	str_hex[7];

	str_hex[0] = get_hex(r / 16);
	str_hex[1] = get_hex(fmod(r, 16));
	str_hex[2] = get_hex(g / 16);
	str_hex[3] = get_hex(fmod(g, 16));
	str_hex[4] = get_hex(b / 16);
	str_hex[5] = get_hex(fmod(b, 16));
	str_hex[6] = '\0';
	return (ft_atoi_base(str_hex, "0123456789ABCDEF"));
}
