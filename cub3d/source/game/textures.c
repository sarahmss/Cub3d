/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 18:59:18 by smodesto          #+#    #+#             */
/*   Updated: 2022/08/15 19:46:19 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	copy_layer(t_image *from, t_image *to)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++j < from->height)
	{
		while (++i < from->width * (from->bpp / 8))
		{
			if (to->data_address[(int)(i + (j * to->line_size))] == BLACK)
			to->data_address[(int)(i + (j * to->line_size))]
					= from->data_address[i + j * from->line_size];
		}
		i = -1;
	}
}

static int	convert_xpm_to_img(t_mlx *mlx, t_scene *s, t_image *text[4])
{
	t_textures	t;

	t = T_NO;
	while (t <= T_EA)
	{
		text[t]->img = mlx_xpm_file_to_image(mlx->mlx, s->no_texture,
				&text[t]->width, &text[t]->height);
		if (text[t]->img == NULL)
			return (check_error(-1, "INVALID XPM FILE"));
		t++;
	}
	return (0);
}

static int	get_texture_data(t_image *no, t_image *so, t_image *we, t_image *ea)
{
	no->data_address = mlx_get_data_addr(no->img, &no->bpp, &no->line_size,
			&no->endian);
	so->data_address = mlx_get_data_addr(so->img, &so->bpp, &so->line_size,
			&so->endian);
	we->data_address = mlx_get_data_addr(we->img, &we->bpp, &we->line_size,
			&we->endian);
	ea->data_address = mlx_get_data_addr(ea->img, &ea->bpp, &ea->line_size,
			&ea->endian);
	return (0);
}

int	handle_textures(t_cub3d *data, t_image *text[4])
{
	if (convert_xpm_to_img(data->mlx, data->scene, text) == -1)
		exit (before_living(data));
	get_texture_data(text[T_NO], text[T_SO], text[T_WE], text[T_EA]);
	init_background(data, data->win_width, data->win_height, data->scene);
	return (0);
}
