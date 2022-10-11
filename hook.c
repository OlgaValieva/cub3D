/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carys <carys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:01:00 by carys             #+#    #+#             */
/*   Updated: 2022/10/11 10:00:57 by carys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	red_cross(t_data *d)
{
	printf(COLOR"🌈 Don't worry, try again\n");
	game_end(d);
	return (0);
}

double	convert_to_rad(double angle)
{
	return (angle * M_PI / 180.0);
}

int	keys(int key, t_data *d)
{
	if (key == 13)
		step_forward(d);
	else if (key == 1)
		step_back(d);
	else if (key == 0)
		step_left(d);
	else if (key == 2)
		step_right(d);
	else if (key == 123)
		turn_left(d);
	else if (key == 124)
		turn_right(d);
	else if (key == 53)
	{
		printf(COLOR"ESC\n");
		red_cross(d);
	}
		
	return (0);
}

t_texture	load_texture(void *mlx, char *filename, t_data *d)
{
	t_texture	texture;

	texture.filename = filename;
	texture.mlx_img_ptr = mlx_xpm_file_to_image(mlx, filename, &(texture.width),
			&(texture.height));
	if (!texture.mlx_img_ptr)
	{
		ft_putstr_fd(texture.filename, 2);
		ft_putstr_fd(": ", 2);
		error_free("reading xpm file from cub3d failed\n", d);
	}
	texture.data = (int *)mlx_get_data_addr(texture.mlx_img_ptr,
			&texture.bits_per_pixel, &texture.size_line, &texture.endian);
	return (texture);
}

void	images(t_data *d)
{
	d->mlx = mlx_init();
	d->north_texture = load_texture(d->mlx, d->north_texture.filename, d);
	d->west_texture = load_texture(d->mlx, d->west_texture.filename, d);
	d->south_texture = load_texture(d->mlx, d->south_texture.filename, d);
	d->east_texture = load_texture(d->mlx, d->east_texture.filename, d);
	d->mlx_win = mlx_new_window(d->mlx, WINDOW_W, WINDOW_H, "Cub3d;)");
}
