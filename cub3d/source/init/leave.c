/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leave.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 23:09:17 by smodesto          #+#    #+#             */
/*   Updated: 2022/07/28 23:13:04 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	free_scene(t_scene *scene)
{
	if (scene->no_texture)
		free(scene->no_texture);
	if (scene->so_texture)
		free(scene->so_texture);
	if (scene->we_texture)
		free(scene->we_texture);
	if (scene->ea_texture)
		free(scene->ea_texture);
	if (scene->cub_map)
		free_array((void **)scene->cub_map, scene->map_height);
	free(scene);
}

/*
	free memory before living
*/
int	before_living(t_cub3d *data)
{
	t_textures	t;

	t = T_NO;
	if (data->scene)
		free_scene(data->scene);
	if (data->mlx->mlx)
		free(data->mlx->mlx);
	if (data->mlx)
		free(data->mlx);
	if (data->img)
		free(data->img);
	while (t <= T_EA)
	{
		if (data->textures[t])
			free(data->textures[t++]);
	}
	if (data->background)
		free(data->background);
	if (data)
		free(data);
	return (0);
}

/*
	Write error messages and exit program
*/
int	check_error(int err, char *msg)
{
	ft_printf("-Error\n: %s\n", msg);
	return (err);
}
