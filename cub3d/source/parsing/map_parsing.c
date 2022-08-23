/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 21:26:02 by smodesto          #+#    #+#             */
/*   Updated: 2022/08/22 21:07:11 by smodesto         ###   ########.fr       */
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
	scene->cub_map = (int **) ft_calloc(sizeof(int *), (scene->map_height));
	if (!(scene->cub_map))
		check_error(-1, "ALLOCATING ERROR");
	i = 0;
	while (i < scene->map_height)
	{
		scene->cub_map[i] = (int *)ft_calloc((scene->map_width), sizeof(int));
		if (!(scene->cub_map[i]))
			check_error(-1, "ALLOCATING ERROR");
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
	scene->map_height = height;
	scene->map_width = width;
}

static int	set_element(char *map_line)
{
	if (*map_line == ' ')
		return (SPACES);
	else if (*map_line == '\t')
		return (TAB);
	else if (*map_line == '0')
		return (EMPTY);
	else if (*map_line == '1')
		return (WALL);
	else if (*map_line == 'N')
		return (N);
	else if (*map_line == 'S')
		return (S);
	else if (*map_line == 'W')
		return (W);
	else if (*map_line == 'E')
		return (E);
	return (check_error(-1, "INVALID CHARACTER IN MAP"));
}

static int	fill_map(char *map_line, t_scene *scene, int line)
{
	int	*cub_line;
	int	i;

	i = 0;
	cub_line = scene->cub_map[line];
	while (*map_line != '\0')
	{
		*cub_line = set_element(map_line);
		if (*cub_line == TAB)
		{
			ft_intset(cub_line, TAB, 4);
			cub_line += 3;
			i += 3;
		}
		if (*cub_line == -1)
			return (-1);
		i++;
		map_line++;
		cub_line++;
	}
	if (i < scene->map_width - 1)
		ft_intset(cub_line, SPACES, (scene->map_width - i - 1));
	return (0);
}

int	map_parsing(char **cub_map, t_scene *scene)
{
	int		i;

	i = 0;
	get_height_width(cub_map, scene);
	if (check_map(cub_map, scene) == -1)
	{
		free_matrix(cub_map);
		return (-1);
	}
	alloc_map(scene);
	while (cub_map[i] != NULL)
	{
		if (fill_map(cub_map[i], scene, i) == -1)
			return (-1);
		i++;
	}
	return (0);
}
