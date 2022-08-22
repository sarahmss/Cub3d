/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 13:42:52 by smodesto          #+#    #+#             */
/*   Updated: 2022/08/22 17:33:55 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_elements(int *elements, t_scene *s)
{
	int	i;

	i = 0;
	while (elements[i] == 1 && i < 6)
		i++;
	free(elements);
	if (i != 6)
		return (check_error(-1, "REPEATED OR MISSING MAP ELEMENTS"));
	if (s->textures[T_NO] == NULL || s->textures[T_SO] == NULL
		|| s->textures[T_WE] == NULL || s->textures[T_EA] == NULL)
		return (check_error(-1, "INVALID TEXTURE PATH"));
	return (0);
}

static int	get_rgb(char *line, int rgb[3], char element)
{
	char	**line_rgb;
	int		i;
	char	*color;

	i = 0;
	color = ft_strchr(line, element);
	if (*(++color) != ' ')
		return (check_error(-1, "INVALID COLORS"));
	line_rgb = ft_split(++color, ',');
	while (line_rgb[i])
	{
		rgb[i] = ft_atoi(line_rgb[i]);
		if (rgb[i] < 0 || rgb[i] > 255 || !ft_strisdigit(line_rgb[i]))
			return (check_error(-1, "INVALID COLORS"));
		i++;
	}
	if (i != 3 || ft_str_count_char(color, ',') > 2)
		return (check_error(-1, "INVALID COLORS"));
	free_matrix(line_rgb);
	return (0);
}

/*
	possivel leak na incrementação do line
*/
static char	*check_path(char *line, int len)
{
	char	*path;
	int		i;
	int		fd;

	i = 0;
	while (i++ < len)
		line++;
	if (line == NULL)
		return (NULL);
	path = ft_strtrim(line, " ");
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		free(path);
		return (NULL);
	}
	close (fd);
	return (path);
}

static int	cpy_elements(t_scene *scene, int *elements, char *line)
{
	if (ft_strncmp("NO", line, 2) == 0 && ++elements[0])
		scene->textures[T_NO] = check_path(line, 3);
	else if (ft_strncmp("SO", line, 2) == 0 && ++elements[1])
		scene->textures[T_SO] = check_path(line, 3);
	else if (ft_strncmp("WE", line, 2) == 0 && ++elements[2])
		scene->textures[T_WE] = check_path(line, 3);
	else if (ft_strncmp("EA", line, 2) == 0 && ++elements[3])
		scene->textures[T_EA] = check_path(line, 3);
	else if (ft_strncmp("F", line, 1) == 0 && ++elements[4])
	{
		if (get_rgb(line, scene->floor_color, 'F') == -1)
			return (-1);
	}
	else if (ft_strncmp("C", line, 1) == 0 && ++elements[5])
	{
		if (get_rgb(line, scene->ceiling_color, 'C') == -1)
			return (-1);
	}
	else
		return (check_error(-1, "UNKNOWN OR MISSING ELEMENTS"));
	return (0);
}

int	get_elements(t_scene *scene, int fd, int i)
{
	char	*line;
	int		*elements;

	elements = (int *)ft_calloc(7, sizeof(int));
	while (i < 6 && get_next_line(fd, &line))
	{
		if (ft_strlen(line))
		{
			if (cpy_elements(scene, elements, line) == -1)
				return (-1);
			i++;
		}
		ft_free_g(&line);
	}
	ft_free_g(&line);
	return (check_elements(elements, scene));
}
