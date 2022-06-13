/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 18:56:26 by smodesto          #+#    #+#             */
/*   Updated: 2021/09/13 11:12:47 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "../libraries/minilibx-linux/mlx.h"
# include "../libraries/libft/libft.h"
# include "./structs.h"
# include "./keymap.h"

t_cub3d	*init_data(void);
void	control_events(t_cub3d *data);
void	check_error(int err, char *msg);
int		before_living(t_cub3d *data);
int		read_file(char *filename, t_scene *scene);
int		map_parsing(char **cub_map, t_scene *scene);
#endif
