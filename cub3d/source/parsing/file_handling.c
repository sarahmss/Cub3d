/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 20:45:09 by smodesto          #+#    #+#             */
/*   Updated: 2022/08/22 17:48:51 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static char	*map_error(char *line, char *map_in_one_line)
{
	if (line[0] == 'C' || line[0] == 'F' || !ft_strncmp(line, "NO", 2)
		|| !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "SO", 2)
		|| !ft_strncmp(line, "EA", 2))
		check_error(-1, "REPEATED OR MISSING MAP ELEMENTS");
	else
		check_error(-1, "INVALID MAP - CHECK EMPTY LINES");
	ft_free_g(&line);
	if (map_in_one_line)
		free (map_in_one_line);
	return (NULL);
}

static char	*skip_empty(int fd)
{
	char	*line;

	line = NULL;
	while (get_next_line(fd, &line))
	{
		if (ft_strlen(line))
			return (line);
		ft_free_g(&line);
	}
	return (line);
}

static char	**copy_map(int fd, char **maptriz, int i)
{
	char	*line;
	char	*map_in_one_line;
	char	*temp;

	line = skip_empty(fd);
	map_in_one_line = ft_strdup(line);
	ft_free_g(&line);
	while (get_next_line(fd, &line))
	{
		if (!ft_strlen(line))
			return ((char **)map_error(line, map_in_one_line));
		else
		{
			temp = map_in_one_line;
			map_in_one_line = ft_join_var(3, map_in_one_line, "\n", line);
			free(temp);
		}
		i++;
		ft_free_g(&line);
	}
	ft_free_g(&line);
	maptriz = ft_split(map_in_one_line, '\n');
	free(map_in_one_line);
	return (maptriz);
}

static int	check_extension(char *filename, char *extension)
{
	int		len;
	char	*ext;

	len = ft_strlen(filename);
	ext = ft_substr(filename, (len - 4), len);
	if (!ft_strcmp(ext, extension))
	{
		free(ext);
		return (check_error(-1, "FILE MUST END WITH [.cub] EXTENSION"));
	}
	free(ext);
	return (0);
}

int	read_file(char *filename, t_scene *scene)
{
	int		fd;
	char	**cub_map;

	cub_map = NULL;
	if (check_extension(filename, ".cub"))
		return (-1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (check_error(-1, "UNABLE TO OPEN FILE"));
	if (get_elements(scene, fd, 0))
		return (-1);
	cub_map = copy_map(fd, cub_map, 0);
	if (cub_map == NULL || map_parsing(cub_map, scene) == -1)
		return (-1);
	free_matrix(cub_map);
	close(fd);
	return (0);
}
