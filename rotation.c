/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:12:18 by carys             #+#    #+#             */
/*   Updated: 2022/10/12 21:51:13 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
Заполняем пол и потолок
*/
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
	(void) y;
	// printf("mouse move min=%5d  max=%5d dir=%5d\n", d->mouse_minp, d->mouse_maxp, x);
	if (x < d->mouse)
		turn_left(d);
	else if (x > d->mouse)
		turn_right(d);
	// if (x > d->mouse_maxp)
	// 	d->mouse_maxp = d->mouse;
	// if (x < d->mouse_minp)
	d->mouse = x;
	return (0);
}
