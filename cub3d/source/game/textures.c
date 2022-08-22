/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 18:59:18 by smodesto          #+#    #+#             */
/*   Updated: 2022/08/22 20:41:05 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	convert_xpm_to_img(t_mlx *mlx, t_scene *s, t_image *text[4])
{
	t_textures	t;

	t = T_NO;
	while (t <= T_EA)
	{
		text[t]->img = mlx_xpm_file_to_image(mlx->mlx, s->textures[t],
				&text[t]->width, &text[t]->height);
		if (text[t]->img == NULL)
			return (check_error(-1, "INVALID XPM FILE"));
		text[t]->data_address = mlx_get_data_addr(text[t]->img, &text[t]->bpp, &text[t]->line_size, &text[t]->endian);
		t++;
	}
	return (0);
}

int	handle_textures(t_cub3d *data, t_image *text[4])
{
	if (convert_xpm_to_img(data->mlx, data->scene, text) == -1)
		exit (before_living(data));
	return (0);
}
