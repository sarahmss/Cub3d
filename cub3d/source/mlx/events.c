/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 10:49:09 by smodesto          #+#    #+#             */
/*   Updated: 2022/07/09 23:52:39 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
	Close window when X bar's buttom is pressed
*/
static int	close_window(t_cub3d *data)
{
	mlx_destroy_image(data->mlx->mlx, data->img->img);
	mlx_destroy_window(data->mlx->mlx, data->mlx->win);
	mlx_destroy_display(data->mlx->mlx);
	before_living(data);
	exit(0);
}

/*
	Controls keyboard events
*/
static int	keyboard_input(int key, t_cub3d *data)
{
	if (key == MAIN_KEY_ESC)
		close_window(data);
	else if (key == ARROW_UP)
		move_forward(data, data->r);
	else if (key == ARROW_DOWN)
		move_backward(data, data->r);
	else if (key == ARROW_RIGHT)
		rotate_right(data);
	else if (key == ARROW_LEFT)
		rotate_left(data);
	return (0);
}

/*
	add following lines to handle keymboard and reload (-)
	mlx_expose_hook(mlx->win, &redraw, mlx);
*/
void	control_events(t_cub3d *data)
{
	mlx_hook(data->mlx->win, X_EVENT_KEY_EXIT, 0, &close_window, data);
	mlx_key_hook(data->mlx->win, keyboard_input, data);
}
