/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 20:45:09 by smodesto          #+#    #+#             */
/*   Updated: 2022/06/22 22:16:03 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	get_rgb(char *line, int rgb[3])
{
	char	**line_rgb;
	int		i;
	char	*color;

	i = 0;
	color = ft_strchr(line, ' ');
	line_rgb = ft_split(++color, ',');
	while (i < 3)
	{
		rgb[i] = ft_atoi(line_rgb[i]);
		i++;
	}
	free_matrix(line_rgb);
}

static void	get_elements(t_scene *scene, int fd)
{
	int		i;
	char	*line;

	i = 0;
	while (get_next_line(fd, &line) && i < 6)
	{
		if (ft_strlen(line))
		{
			if (ft_strncmp("NO", line, 2) == 0)
				scene->no_texture = ft_strdup(ft_strchr(line, '.'));
			else if (ft_strncmp("SO", line, 2) == 0)
				scene->so_texture = ft_strdup(ft_strchr(line, '.'));
			else if (ft_strncmp("WE", line, 2) == 0)
				scene->we_texture = ft_strdup(ft_strchr(line, '.'));
			else if (ft_strncmp("EA", line, 2) == 0)
				scene->ea_texture = ft_strdup(ft_strchr(line, '.'));
			else if (ft_strncmp("F", line, 1) == 0)
				get_rgb(line, scene->floor_color);
			else if (ft_strncmp("C", line, 1) == 0)
				get_rgb(line, scene->ceiling_color);
			i++;
		}
		ft_free_g(&line);
	}
	ft_free_g(&line);
}

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

int	check_map(char **cub_map, t_scene *scene)
{
	int	i;

	i = 0;
	while (cub_map[0][i] != '\0')
		if (ft_strccmp("1 \t", cub_map[0][i++]) == 0)
			return (-1);
	i = 0;
	while (cub_map[scene->map_height][i] != '\0')
		if (ft_strccmp("1 \t", cub_map[scene->map_height][i++]) == 0)
			return (-1);
	i = 0;
	while (i < scene->map_height)
	{
		if (ft_strccmp("1 \t", cub_map[i][0]) == 0)
			return (-1);
		if (ft_strccmp("1 \t", cub_map[i][ft_strlen(cub_map[i]) - 1]) == 0)
			return (-1);
		i++;
	}
	return (0);
}

int	read_file(char *filename, t_scene *scene)
{
	int		fd;
	char	**cub_map;

	cub_map = NULL;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("ERROR - Unable to open %s", filename);
		return (-1);
	}
	get_elements(scene, fd);
	cub_map = copy_map(fd, cub_map, 0);
	if (map_parsing(cub_map, scene) == -1)
		return (-1);
	free_matrix(cub_map);
	close(fd);
	return (0);
}
