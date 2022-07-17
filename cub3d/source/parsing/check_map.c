/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 22:24:29 by smodesto          #+#    #+#             */
/*   Updated: 2022/07/17 18:18:52 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	top_line(char **cub_map)
{
	int	i;

	i = 0;
	while (cub_map[0][i] != '\0')
	{
		while (cub_map[0][i] == '\t' || cub_map[0][i] == ' ')
			i++;
		if (cub_map[0][i] != '1')
		{
			printf ("ERROR- INVALID MAP - CHECK TOP_LINE");
			return (-1);
		}
		i++;
	}
	return (0);
}

static int	bottom_line(char **cub_map, int last_line)
{
	int	i;

	i = 0;
	while (cub_map[last_line][i] != '\0')
	{
		while (cub_map[last_line][i] == '\t' || cub_map[last_line][i] == ' ')
			i++;
		if (cub_map[last_line][i] != '1')
		{
			printf ("ERROR- INVALID MAP - CHECK BOTTOM LINE");
			return (-1);
		}
		i++;
	}
	return (0);
}

static int	left_column(char **cub_map, int lines)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < lines)
	{
		while (cub_map[i][0 + j] == '\t' || cub_map[i][0 + j] == ' ')
			j++;
		if (cub_map[i][0 + j] != '1')
		{
			printf ("ERROR- INVALID MAP - CHECK LEFT COLUMN");
			return (-1);
		}
		i++;
	}
	return (0);
}

static int	right_column(char **cub_map, int lines)
{
	int	i;

	i = 0;
	while (i < lines)
	{
		if (cub_map[i][ft_strlen(cub_map[i]) - 1] != '1')
		{
			printf ("ERROR- INVALID MAP - CHECK RIGHT COLUMN");
			return (-1);
		}
		i++;
	}
	return (0);
}

int	check_map(char **cub_map, t_scene *scene)
{
	int	i;
	int	valid;

	i = -1;
	valid = 0;
	if (top_line(cub_map) == -1)
		return (-1);
	if (bottom_line(cub_map, scene->map_height - 1) == -1)
		return (-1);
	if (left_column(cub_map, scene->map_height) == -1)
		return (-1);
	if (right_column(cub_map, scene->map_height) == -1)
		return (-1);
	while (cub_map[++i] != NULL)
	{
		if (ft_strchr(cub_map[i], 'N') || ft_strchr(cub_map[i], 'S')
			|| ft_strchr(cub_map[i], 'W') || ft_strchr(cub_map[i], 'E'))
			valid++;
	}
	if (valid != 1)
	{
		printf ("ERROR- INVALID MAP - CHECK NSWE");
		return (-1);
	}
	return (0);
}
