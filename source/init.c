/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 19:27:02 by smodesto          #+#    #+#             */
/*   Updated: 2022/06/15 23:30:27 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static t_scene	*init_scene(void)
{
	t_scene	*scene;

	scene = (t_scene *)malloc(sizeof(t_scene));
	scene->no_texture = NULL;
	scene->so_texture = NULL;
	scene->we_texture = NULL;
	scene->ea_texture = NULL;
	bzero(scene->floor_color, 3);
	bzero(scene->ceiling_color, 3);
	scene->map_height = 0;
	scene->map_width = 0;
	scene->cub_map = NULL;
	return (scene);
}

/*
** allocate and init cub3d data structure
*/
t_cub3d	*init_data(void)
{
	t_cub3d	*data;

	data = (t_cub3d *)malloc(sizeof(t_cub3d));
	if (!data)
		check_error(1, "ERR_FDF_INIT");
	data->mlx = NULL;
	data->win = NULL;
	data->scene = init_scene();
	return (data);
}
