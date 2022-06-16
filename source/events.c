/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 10:49:09 by smodesto          #+#    #+#             */
/*   Updated: 2022/06/15 23:30:19 by smodesto         ###   ########.fr       */
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
		free_matrix((char **)scene->cub_map);
}

/*
	free memory before living
*/
int	before_living(t_cub3d *data)
{
	if (data->scene)
		free_scene(data->scene);
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

/*
	Close window when X bar's buttom is pressed
*/
static int	close_window(t_cub3d *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data);
	exit(0);
}

void	control_events(t_cub3d *data)
{
//	mlx_key_hook(data->win, keyboard_input, data);
	mlx_hook(data->win, X_EVENT_KEY_EXIT, 0, &close_window, data);
//	mlx_expose_hook(mlx->win, &redraw, mlx);
}
