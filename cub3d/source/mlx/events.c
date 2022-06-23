/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 10:49:09 by smodesto          #+#    #+#             */
/*   Updated: 2022/06/22 23:55:09 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
	Close window when X bar's buttom is pressed
*/
static int	close_window(t_cub3d *data)
{
	mlx_destroy_window(data->mlx->mlx, data->mlx->win);
	ft_create_image(data->mlx, data->img);
	mlx_destroy_display(data->mlx->mlx);
	before_living(data);
	exit(0);
}

/*
	Controls keyboard events
static int	keyboard_input(int key, t_cub3d *data)
{
	if (key == MAIN_KEY_ESC)
		close_window(data);
	else if (key == ARROW_UP)
		move_forward(key, mlx);
	else if (key == ARROW_DOWN)
		move_backward(key, mlx);
	else if (key == ARROW_RIGHT)
		rotate_right();
	else if (key == ARROW_LEFT)
		rotate_left();
	return (0);
}
*/

/*
	add following lines to handle keymboard and reload (-)
	mlx_expose_hook(mlx->win, &redraw, mlx);
	mlx_key_hook(data->win, keyboard_input, data);
*/
void	control_events(t_cub3d *data)
{
	mlx_hook(data->mlx->win, X_EVENT_KEY_EXIT, 0, &close_window, data);
}
