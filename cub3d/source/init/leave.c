/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leave.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 23:09:17 by smodesto          #+#    #+#             */
/*   Updated: 2022/08/22 20:50:11 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_scene(t_scene *scene)
{
	t_textures	t;

	t = T_NO;
	while (t <= T_EA)
	{
		if (scene->textures[t])
			free (scene->textures[t]);
		t++;
	}
	if (scene->cub_map)
		free_array((void **)scene->cub_map, scene->map_height);
	free(scene);
}

void	clean_images(t_cub3d *data)
{
	t_textures	t;

	t = T_NO;
	if (data->img)
	{
		mlx_destroy_image(data->mlx->mlx, data->img->img);
		free(data->img);
	}
	while (t <= T_EA)
	{
		if (data->textures[t])
		{
			mlx_destroy_image(data->mlx->mlx, data->textures[t]->img);
			free(data->textures[t]);
		}
		t++;
	}
}

/*
	free memory before living
*/
int	before_living(t_cub3d *data)
{
	clean_images(data);
	if (data->scene)
		free_scene(data->scene);
	if (data->mlx->mlx)
		free(data->mlx->mlx);
	if (data->mlx)
		free(data->mlx);
	if (data)
		free(data);
	return (0);
}

/*
	Write error messages and exit program
*/
int	check_error(int err, char *msg)
{
	ft_printf("           -Error\n    %s\n", msg);
	return (err);
}
