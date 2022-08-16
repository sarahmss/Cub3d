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

int	check_x_inverse_offset(t_raycasting ray, int texture_offset)
{
	if (ray.hit_side == HORIZONTAL && is_ray_facing_down(ray.ray_angle))
		return (TILE_SIZE - texture_offset);
	if (ray.hit_side == VERTICAL && is_ray_facing_left(ray.ray_angle))
		return (TILE_SIZE - texture_offset);
	return (texture_offset);
}

int	get_x_offset(t_raycasting ray)
{
	int	offset;

	if (ray.hit_side == VERTICAL)
		offset = (int)ray.wall_hit.y % TILE_SIZE;
	else
		offset = (int)ray.wall_hit.x % TILE_SIZE;
	offset = check_x_inverse_offset(ray, offset);
	return (offset);
}
