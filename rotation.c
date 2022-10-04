/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carys <carys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:12:18 by carys             #+#    #+#             */
/*   Updated: 2022/10/04 20:22:22 by carys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	paint_window(t_data *d)
{
	unsigned int	*adr;
	int				bpp;
	int				size_line;
	int				endian;
	int				i;

	i = 0;
	adr = (unsigned int *)mlx_get_data_addr(d->img, &bpp, &size_line, &endian);
	while (i < WINDOW_W * (WINDOW_H / 2))
	{
		adr[i] = mlx_get_color_value(d->mlx, d->c_color);
		i++;
	}
	while (i < WINDOW_W * WINDOW_H)
	{
		adr[i] = mlx_get_color_value(d->mlx, d->f_color);
		i++;
	}
}

double	add_angle(double angle, double add)
{
	double	new_angle;

	new_angle = angle + add;
	if (new_angle < 0.0)
		new_angle += 360.0;
	else if (new_angle > 360.0)
		new_angle -= 360.0;
	return (new_angle);
}

void	turn_left(t_data *d)
{
	d->view_angle = add_angle(d->view_angle, -SPEED_ROTATION);
}

void	turn_right(t_data *d)
{
	d->view_angle = add_angle(d->view_angle, SPEED_ROTATION);
}

int	mouse(int x, int y, t_data *d)
{
	if (x < d->mouse)
		turn_left(d);
	else if (x > d->mouse)
		turn_right(d);
	d->mouse = x;
	if (y)
		return (0);
	return (0);
}
