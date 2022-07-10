/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 20:57:45 by smodesto          #+#    #+#             */
/*   Updated: 2022/07/09 21:29:27 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_ray_facing_down(double angle)
{
	return (angle > 0 && angle < M_PI);
}

int	is_ray_facing_up(double angle)
{
	return (!is_ray_facing_down(angle));
}

int	is_ray_facing_right(double angle)
{
	return (angle < 0.5 * M_PI || angle > 1.5 * M_PI);
}

int	is_ray_facing_left(double angle)
{
	return (!is_ray_facing_right(angle));
}
