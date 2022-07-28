/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 19:27:02 by smodesto          #+#    #+#             */
/*   Updated: 2022/07/28 13:59:46 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
	allocate and init IMG struct
*/
t_image	*init_img(int width, int height)
{
	t_image	*img;

	img = (t_image *)malloc(sizeof(t_image));
	if (!img)
		return (NULL);
	img->img = NULL;
	img->data_address = NULL;
	img->bpp = 0;
	img->line_size = 0;
	img->endian = 0;
	img->width = width;
	img->height = height;
	return (img);
}

/*
	allocate and init mlx data structure
*/
t_mlx	*init_mlx(void)
{
	t_mlx	*data;

	data = (t_mlx *)malloc(sizeof(t_mlx));
	if (!data)
		return (NULL);
	data->mlx = NULL;
	data->win = NULL;
	return (data);
}

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
t_cub3d	*init_data(char *argv)
{
	t_cub3d		*data;
	t_textures	t;

	data = (t_cub3d *)malloc(sizeof(t_cub3d));
	if (!data)
		check_error(-1, "Error\n - allocating error");
	data->scene = init_scene();
	data->mlx = init_mlx();
	if (read_file(argv, data->scene) != 0)
		exit (before_living(data));
	data->win_width = data->scene->map_width * TILE_SIZE;
	data->win_height = data->scene->map_height * TILE_SIZE;
	data->img = init_img(data->win_width, data->win_height);
	data->num_rays = data->win_width;
	data->rays = NULL;
	data->fov = 60 * (M_PI / 180);
	t = T_NO;
	while (t <= T_EA)
		data->textures[t++] = init_img(0, 0);
	return (data);
}
