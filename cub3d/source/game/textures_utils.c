/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ttures_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 21:45:31 by smodesto          #+#    #+#             */
/*   Updated: 2022/07/27 21:55:28 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

unsigned int	get_wall_pixel_color(t_image *img, int x, int y)
{
	char	*color;

	if (x < 0 || x > img->width
		|| y < 0 || y > img->height)
	{
		return (1);
	}
	color = img->data_address + (y * img->line_size + x * (img->bpp / 8));
	return (*(unsigned int *)color);
}

int	get_facing_side(double ray_angle, t_side side)
{
	if (side == HORIZONTAL && is_ray_facing_up(ray_angle))
		return (T_NO);
	if (side == HORIZONTAL && is_ray_facing_down(ray_angle))
		return (T_SO);
	if (side == VERTICAL && is_ray_facing_left(ray_angle))
		return (T_WE);
	if (side == VERTICAL && is_ray_facing_right(ray_angle))
		return (T_EA);
	return (0);
}

static int	check_x_offset(t_raycasting ray, int texture_offset, int tile_size)
{
	if (ray.hit_side == HORIZONTAL && is_ray_facing_down(ray.ray_angle))
		return (tile_size - texture_offset);
	if (ray.hit_side == VERTICAL && is_ray_facing_left(ray.ray_angle))
		return (tile_size - texture_offset);
	return (texture_offset);
}

int	get_x_offset(t_raycasting ray, int tile_size)
{
	int	offset;

	if (ray.hit_side == VERTICAL)
		offset = (int)ray.wall_hit.y % tile_size;
	else
		offset = (int)ray.wall_hit.x % tile_size;
	offset = check_x_offset(ray, offset, tile_size);
	return (offset);
}
