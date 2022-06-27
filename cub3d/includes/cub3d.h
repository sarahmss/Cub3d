/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 23:29:38 by smodesto          #+#    #+#             */
/*   Updated: 2022/06/27 10:29:02 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "../libraries/minilibx-linux/mlx.h"
# include "../libraries/libft/libft.h"
# include "./raycasting.h"
# include "./my_mlx_draw.h"
# include "./keymap.h"

typedef enum e_map
{
	EMPTY,
	WALL,
	N,
	S,
	W,
	E,
	SPACES,
	TAB
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
}			t_scene;

typedef struct s_cub3d
{
	t_scene		*scene;
	t_mlx		*mlx;
	t_image		*img;
}				t_cub3d;

//	init
t_cub3d			*init_data(void);
void			check_error(int err, char *msg);
int				before_living(t_cub3d *data);

//	Parsing
int				read_file(char *filename, t_scene *scene);
int				map_parsing(char **cub_map, t_scene *scene);
int				check_map(char **cub_map, t_scene *scene);

//	events
void			control_events(t_cub3d *data);

//	img
void			ft_create_image(t_mlx *mlx, t_image *img, t_cub3d *data);

//	main raycasting
void			raycasting(t_image *img, t_cub3d *data);
t_raycasting	define_points(t_scene *scn);

#endif
