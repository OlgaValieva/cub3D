/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carys <carys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:11:16 by carys             #+#    #+#             */
/*   Updated: 2022/10/04 20:22:18 by carys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_coord	make_coord(t_data d)
{
	t_coord	coord;

	coord.x = d.player_x;
	coord.y = d.player_y;
	return (coord);
}

void	init_ray(t_comp *comp, t_data d, double angle, t_coord *coord)
{
	comp->ray_dir_x = sin(convert_to_rad(angle));
	comp->ray_dir_y = -cos(convert_to_rad(angle));
	comp->delta_dist_x = fabs(1 / comp->ray_dir_x);
	comp->delta_dist_y = fabs(1 / comp->ray_dir_y);
	if (comp->ray_dir_x < 0)
	{
		comp->step_x = -1;
		comp->side_dist_x = (d.player_x - coord->x) * comp->delta_dist_x;
	}
	else
	{
		comp->step_x = 1;
		comp->side_dist_x = (coord->x + 1.0 - d.player_x) * comp->delta_dist_x;
	}
	if (comp->ray_dir_y < 0)
	{
		comp->step_y = -1;
		comp->side_dist_y = (d.player_y - coord->y) * comp->delta_dist_y;
	}
	else
	{
		comp->step_y = 1;
		comp->side_dist_y = (coord->y + 1.0 - d.player_y) * comp->delta_dist_y;
	}
}

void	add_ray(t_comp *comp, t_ray *ray, t_coord *coords)
{
	if (comp->side_dist_y < comp->side_dist_x)
	{
		comp->side_dist_y += comp->delta_dist_y;
		coords->y += comp->step_y;
		ray->side = 'N';
		if (comp->ray_dir_y > 0)
			ray->side = 'S';
	}
	else
	{
		comp->side_dist_x += comp->delta_dist_x;
		coords->x += comp->step_x;
		ray->side = 'W';
		if (comp->ray_dir_x > 0)
			ray->side = 'E';
	}
}

t_ray	add_ray_wall(t_ray ray, t_data d, t_comp comp)
{
	if (ray.side == 'E' || ray.side == 'W')
	{
		ray.distance = comp.side_dist_x - comp.delta_dist_x;
		ray.wall_x = d.player_y + ray.distance * comp.ray_dir_y;
	}
	else
	{
		ray.distance = comp.side_dist_y - comp.delta_dist_y;
		ray.wall_x = d.player_x + ray.distance * comp.ray_dir_x;
	}
	ray.wall_x -= floor(ray.wall_x);
	return (ray);
}

t_ray	ray_cast(t_data d, double angle)
{
	t_comp	comp;
	t_coord	coord;
	t_ray	ray;

	coord = make_coord(d);
	init_ray(&comp, d, angle, &coord);
	while (1)
	{
		add_ray(&comp, &ray, &coord);
		if (d.map[coord.y][coord.x] == '1')
			break ;
	}
	ray.tile = d.map[coord.y][coord.x];
	ray = add_ray_wall(ray, d, comp);
	return (ray);
}
