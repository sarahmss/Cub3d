/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leave.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 23:09:17 by smodesto          #+#    #+#             */
/*   Updated: 2022/06/22 23:29:44 by smodesto         ###   ########.fr       */
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
	if (data->scene)
		free_scene(data->scene);
	if (data->mlx)
		free(data->mlx);
	if (data->img)
		free(data->img);
	if (data)
		free(data);
	return (0);
}

/*
	Write error messages and exit program
*/
void	check_error(int err, char *msg)
{
	if (err < 1)
	{
		ft_printf("-ERROR: %s\n", msg);
		exit (1);
	}
}
