/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 17:58:28 by smodesto          #+#    #+#             */
/*   Updated: 2022/06/23 01:25:15 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_cub3d	*data;
	t_mlx	*mlx;

	if (argc != 2)
	{
		printf("Insert only one file: ./cub3d <file.cub> \n");
		exit (0);
	}
	data = init_data();
	mlx = data->mlx;
	if (read_file(argv[1], data->scene) != 0)
		return (before_living(data));
	for (int i = 0; i < data->scene->map_height; i++)
	{
		for (int j = 0; j < data->scene->map_width; j++)
		{
			printf("%d ", data->scene->cub_map[i][j]);
		}
		printf ("\n");
	}
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	ft_create_image(mlx, data->img, data);
	control_events(data);
	mlx_loop(data->mlx->mlx);
	before_living(data);
	return (0);
}
