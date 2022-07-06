/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 17:58:28 by smodesto          #+#    #+#             */
/*   Updated: 2022/07/06 14:09:59 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_map(int w, int h, int **map)
{
	int	i;
	int	j;

	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			printf("%d ", map[i][j]);
			j++;
		}
		printf ("\n");
		i++;
	}
}

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
	print_map(data->scene->map_width, data->scene->map_height,
		data->scene->cub_map);
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	draw_game(data, mlx, data->img);
	control_events(data);
	mlx_loop(data->mlx->mlx);
	before_living(data);
	return (0);
}
