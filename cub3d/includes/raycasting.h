/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 22:04:46 by smodesto          #+#    #+#             */
/*   Updated: 2022/08/22 16:08:37 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "../includes/cub3d.h"

# define TILE_SIZE			24
# define WALL_STRIP_WIDTH	2
# define MM_SCALE_FACTOR	0.2

typedef enum e_side
{
	HORIZONTAL,
	VERTICAL
}				t_side;

// turn and walk directions
typedef enum e_movement
{
	STOP,
	LEFT = -1,
	RIGHT = 1,
	BACK = -1,
	FRONT = 1,
}				t_movement;

typedef struct s_point
{
	double	x;
	double	y;
}				t_point;

typedef struct s_player
{
	t_point	pos;
	double	radius;
	double	rotation_angle;
	int		move_speed;
	double	rotation_speed;
}				t_player;

typedef struct s_raycasting
{
	int			**cub_map;
	t_player	player;
	t_point		wall_hit;
	t_point		step;
	t_point		intercept;
	t_point		next_touch;
	t_side		hit_side;
	double		distance;
	double		ray_angle;
}				t_raycasting;

// ray direction
int		is_ray_facing_down(double angle);
int		is_ray_facing_up(double angle);
int		is_ray_facing_right(double angle);
int		is_ray_facing_left(double angle);

// math.c
double	distance_between_points(t_point p1, t_point p2);
double	normalize_angle(double angle);

// set_poin.c
t_point	set_step(double ray_angle, t_side side);
t_point	set_intercept(double ray_angle, t_point pos, t_side side);
t_point	set_map(double ray_angle, t_point next_touch, t_side s, t_point wh);

#endif
