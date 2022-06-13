/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 08:51:24 by smodesto          #+#    #+#             */
/*   Updated: 2022/06/12 20:59:29 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# define WIN_WIDTH		1280
# define WIN_HEIGHT		600
# define MENU_WIDTH		200

# define WIN_CENTER_X	400
# define WIN_CENTER_Y	300

typedef enum e_map
{
	SPACES = -1,
	EMPTY,
	WALL,
	N,
	S,
	W,
	E
}				t_map;

typedef struct s_scene
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		floor_color[3];
	int		ceiling_color[3];
	int		map_height;
	int		map_width;
	int		**cub_map;
}				t_scene;

typedef struct s_cub3d
{
	void		*mlx;
	void		*win;
	t_scene		*scene;
}				t_cub3d;

#endif
