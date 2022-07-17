/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 17:58:28 by smodesto          #+#    #+#             */
/*   Updated: 2022/07/17 18:05:38 by smodesto         ###   ########.fr       */
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

/*
*/
void	draw_game(t_cub3d *data, t_mlx *mlx, t_image *img)
{
	t_point	init;
	t_point	end;
	int		wh[2];

	wh[0] = data->win_width;
	wh[1] = data->win_height;
	cast_all_rays(data);
	ft_create_image(mlx, img, wh[0], wh[1]);
	background(img, data->scene->floor_color, data->scene->ceiling_color, wh);
	render_walls(data, init, end);
	draw_minimap(data, data->scene, data->img);
	if (data->rays)
		free(data->rays);
	mlx_put_image_to_window(mlx->mlx, mlx->win, img->img, 0, 0);
}

int	main(int argc, char **argv)
{
	t_cub3d	*data;

	if (argc != 2)
	{
		printf("Insert only one file: ./cub3d <file.cub> \n");
		exit (0);
	}
	data = init_data(argv[1]);
	print_map(data->scene->map_width, data->scene->map_height,
		data->scene->cub_map);
	data->mlx->mlx = mlx_init();
	data->mlx->win = mlx_new_window(data->mlx->mlx, data->win_width,
			data->win_height, "cub3D");
	data->r = define_points(data->scene);
	draw_game(data, data->mlx, data->img);
	control_events(data);
	mlx_loop(data->mlx->mlx);
	before_living(data);
	return (0);
}
