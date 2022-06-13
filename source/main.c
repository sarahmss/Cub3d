/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 17:58:28 by smodesto          #+#    #+#             */
/*   Updated: 2022/06/12 21:16:03 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_cub3d	*data;

	if (argc != 2)
	{
		printf("Insert only one file: ./cub3d <file.cub> \n");
		exit (0);
	}
	data = init_data();
	if (read_file(argv[1], data->scene) != 0)
		return (before_living(data));
/*	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	control_events(data);
	mlx_loop(data->mlx);*/
	return (0);
}
