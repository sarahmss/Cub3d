/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_draw.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 23:16:56 by smodesto          #+#    #+#             */
/*   Updated: 2022/06/22 23:56:12 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#ifndef MY_MLX_DRAW_H
# define MT_MLX_DRAW_H

# define WIN_WIDTH			640
# define WIN_HEIGHT			480

//Colors
# define RED				0XFF2222
# define GREEN				0X22FF22
# define BLUE				0X2222FF
# define PURPLE				0XFF22FF
# define WHITE				0XFFFFFF
# define GREY				0XAAAAAA
# define DGREY				0X444444
# define BACKGROUND			0X222222
# define MENU_BACKGROUND	1973790
# define TEXT_COLOR			0XEAEAEA

typedef struct s_line
{
	int		height;
	double	x0;
	double	y0;
	double	x1;
	double	y1;
	int		delta_x;
	int		delta_y;
	int		max;
}				t_line;

typedef struct s_image
{
	int			*img;
	char		*data_address;
	int			bpp;
	int			line_size;
	int			endian;
	int			width;
	int			height;
}				t_image;

typedef struct t_mlx
{
	void		*mlx;
	void		*win;
}				t_mlx;


//	draw
void	brasenham(t_line line, t_image *img, int color);
void	draw_vertical_line(t_image *img, int x, int begin, int end ,int color);

//	img
void	my_mlx_pixel_put(int x, int y, t_image *img, int color);
void	background(t_image *img);
void	ft_create_image(t_mlx *mlx, t_image *img);

//	init
t_image	*init_img(int width, int height);
t_mlx	*init_mlx(void);

//	main raycasting
void	raycasting(t_image *img);
#endif
