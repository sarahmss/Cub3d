/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 13:42:52 by smodesto          #+#    #+#             */
/*   Updated: 2022/07/27 21:20:46 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_elements(int elements[6], t_scene *s)
{
	int	i;

	i = 0;
	if (s->no_texture == NULL || s->so_texture == NULL
		|| s->we_texture == NULL || s->ea_texture == NULL)
		return (check_error(-1, "INVALID PATH"));
	while (elements[i] == 1 && i < 6)
		i++;
	if (i == 6)
		return (0);
	return (check_error(-1, "REPEATED OR MISSING MAP ELEMENTS"));
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
	while (i < 3)
	{
		rgb[i] = ft_atoi(line_rgb[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (check_error(-1, "INVALID COLORS"));
		i++;
	}
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

static int	cpy_elements(t_scene *scene, int elements[6], char *line)
{
	if (ft_strncmp("NO", line, 2) == 0 && ++elements[0])
		scene->no_texture = check_path(line, 3);
	else if (ft_strncmp("SO", line, 2) == 0 && ++elements[1])
		scene->so_texture = check_path(line, 3);
	else if (ft_strncmp("WE", line, 2) == 0 && ++elements[2])
		scene->we_texture = check_path(line, 3);
	else if (ft_strncmp("EA", line, 2) == 0 && ++elements[3])
		scene->ea_texture = check_path(line, 3);
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
		return (check_error(-1, "UNKNOWN ELEMENTS"));
	return (0);
}

int	get_elements(t_scene *scene, int fd, int i)
{
	char	*line;
	int		elements[6];

	while (i < 6)
		elements[i++] = 0;
	i = 0;
	while (get_next_line(fd, &line) && i < 6)
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
