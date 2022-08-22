/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leave.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 23:09:17 by smodesto          #+#    #+#             */
/*   Updated: 2022/08/22 16:06:42 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	free_scene(t_scene *scene)
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

static void	clean_images(t_cub3d *data)
{
	t_textures	t;

	t = T_NO;
	if (data->img)
	{
		free(data->img);
	}
	while (t <= T_EA)
	{
		if (data->textures[t])
		{
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
