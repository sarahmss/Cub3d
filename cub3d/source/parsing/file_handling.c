/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 20:45:09 by smodesto          #+#    #+#             */
/*   Updated: 2022/07/26 14:22:12 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static char	**copy_map(int fd, char **maptriz, int i)
{
	char	*line;
	char	*map_in_one_line;
	char	*temp;

	while (get_next_line(fd, &line))
	{
		if (ft_strlen(line))
		{
			if (i == 0)
				map_in_one_line = ft_strdup(line);
			else
			{
				temp = map_in_one_line;
				map_in_one_line = ft_join_var(3, map_in_one_line, "\n", line);
				free(temp);
			}
			i++;
		}
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
		printf("ERROR - [%s] must end with .cub extension\n", filename);
		return (-1);
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
	{
		printf("ERROR - Unable to open %s\n", filename);
		return (-1);
	}
	if (get_elements(scene, fd, 0))
		return (-1);
	cub_map = copy_map(fd, cub_map, 0);
	if (map_parsing(cub_map, scene) == -1)
		return (-1);
	free_matrix(cub_map);
	close(fd);
	return (0);
}
