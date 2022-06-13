/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 21:26:02 by smodesto          #+#    #+#             */
/*   Updated: 2022/06/12 23:02:15 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
	Allocate memory to cub map
*/
static void	alloc_map(t_scene *scene)
{
	int	i;

	i = 0;
	scene->cub_map = (int **) malloc(sizeof(int *) * (scene->map_height + 1));
	if (!(scene->cub_map))
		check_error(1, "ALLOCATING ERROR");
	i = 0;
	while (i < scene->map_height)
	{
		scene->cub_map[i] = (int *)malloc(sizeof(int) * (scene->map_width + 1));
		if (!(scene->cub_map[i]))
			check_error(1, "ALLOCATING ERROR");
		i++;
	}
}

/*
	get_heght_width function uses gnl to read each line of a
	file and then storage the amount of rows and columns
	with the help of ft_split
*/
static void	get_height_width(char **cub_map, t_scene *scene)
{
	int		height;
	int		width;
	int		len;

	height = 0;
	width = 0;
	while (cub_map[height] != NULL)
	{
		len = ft_strlen(cub_map[height]);
		if (len > width)
			width = len;
		height++;
	}
	scene->map_height = height - 1;
	scene->map_width = width - 1;
}

static void	fill_map(char *map_line, t_scene *scene, int line)
{
	int		i;
	int		j;
	int		spaces;

	i = 0;
	spaces = 0;
	while (map_line[i])
	{
		if (map_line[i] == '\t')
			while (spaces++ < 4)
				scene->cub_map[line][j++] = SPACES;
		else if (map_line[i] == ' ')
			scene->cub_map[line][j] = SPACES;
		else if (map_line[i] == '0')
			scene->cub_map[line][j] = EMPTY;
		else if (map_line[i] == '1')
			scene->cub_map[line][j] = WALL;
		else if (map_line[i] == 'N')
			scene->cub_map[line][j] = N;
		else if (map_line[i] == 'S')
			scene->cub_map[line][j] = S;
		else if (map_line[i] == 'W')
			scene->cub_map[line][j] = W;
		else if (map_line[i] == 'E')
			scene->cub_map[line][j] = E;
		i++;
		j++;
	}
}

int	check_map(char **cub_map, t_scene *scene)
{
	int	i;

	i = 0;
	while (cub_map[0][i])
		if (ft_strchr("1 \t", cub_map[0][i++]) == NULL)
			return (-1);
	i = 0;
	while (cub_map[scene->map_height][i])
		if (ft_strchr("1 \t", cub_map[scene->map_height][i++]) == NULL)
			return (-1);
	i = 0;
	while (cub_map[i][0])
		if (ft_strchr("1 \t", cub_map[i++][0]) == NULL)
			return (-1);
	i = 0;
	while (cub_map[i][scene->map_width])
		if (ft_strchr("1 \t", cub_map[i++][scene->map_width]) == NULL)
			return (-1);
	return (0);
}

int	map_parsing(char **cub_map, t_scene *scene)
{
	int		i;

	i = 0;
	get_height_width(cub_map, scene);
/*	if (check_map(cub_map, scene))
	{
		free_matrix(cub_map);
		printf ("ERROR- INVALID MAP");
		return (-1);
	}*/
	alloc_map(scene);
	while (cub_map[i] != NULL)
	{
		fill_map(cub_map[i], scene, i);
		i++;
	}
	return (0);
}
