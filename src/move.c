/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carys <carys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:09:10 by carys             #+#    #+#             */
/*   Updated: 2022/10/04 15:09:41 by carys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "..cub3d.h"

int	cast(t_data *d, int add)
{
	t_ray	ray;

	ray = ray_cast(*d, add_angle(d->view_angle, add));
	if (ray.distance < WALL_DIST)
		return (1);
	return (0);
}

void	step_forward(t_data *d)
{
	double	dx;
	double	dy;

	dx = -sin(convert_to_rad(d->view_angle)) * SPEED_MOVE;
	dy = cos(convert_to_rad(d->view_angle)) * SPEED_MOVE;
	if (!cast(d, 0))
	{
		d->player_x -= dx;
		d->player_y -= dy;
	}
}

void	step_back(t_data *d)
{
	double	dx;
	double	dy;

	dx = -sin(convert_to_rad(d->view_angle)) * SPEED_MOVE;
	dy = cos(convert_to_rad(d->view_angle)) * SPEED_MOVE;
	if (!cast(d, 180))
	{
		d->player_x += dx;
		d->player_y += dy;
	}
}

void	step_left(t_data *d)
{
	double	dx;
	double	dy;

	dx = -cos(convert_to_rad(d->view_angle)) * SPEED_MOVE;
	dy = -sin(convert_to_rad(d->view_angle)) * SPEED_MOVE;
	if (!cast(d, 270))
	{
		d->player_x += dx;
		d->player_y += dy;
	}
}

void	step_right(t_data *d)
{
	double	dx;
	double	dy;

	dx = cos(convert_to_rad(d->view_angle)) * SPEED_MOVE;
	dy = sin(convert_to_rad(d->view_angle)) * SPEED_MOVE;
	if (!cast(d, 90))
	{
		d->player_x += dx;
		d->player_y += dy;
	}
}