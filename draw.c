/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 12:45:15 by carys             #+#    #+#             */
/*   Updated: 2022/10/11 14:12:53 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	choose_text(t_texture *text, t_data d, t_ray ray)
{
	if (ray.side == 'N')
		(*text) = d.north_texture;
	else if (ray.side == 'E')
		(*text) = d.east_texture;
	else if (ray.side == 'S')
		(*text) = d.south_texture;
	else
		(*text) = d.west_texture;
}

/*
function for calculate color in texture
*/
unsigned int	color(t_texture texture, t_ray ray, int tex_pos)
{
	t_size			tex_coord;
	unsigned int	color;

	tex_coord.x = ray.wall_x * (double)texture.width;
	if (ray.side == 'E')
		tex_coord.x = texture.width - tex_coord.x - 1;
	if (ray.side == 'S')
		tex_coord.x = texture.width - tex_coord.x - 1;
	tex_coord.y = tex_pos & (texture.height - 1);
	color = texture.data[texture.width * tex_coord.y + tex_coord.x];
	if (ray.side == 'W' || ray.side == 'E')
		color = (color >> 1) & 8355711;
	return (color);
}
// 8355711 wtf

void	draw_wide_pixel(t_data d, int x, int y, unsigned int color)
{
	int	idx;

	idx = -1;
	while (++idx < GFX_QUALITY + 1)
		image_pixel_put(d, x + idx, y, color);
}

void	wall(t_data d, t_ray ray, int ray_number)
{
	t_texture		text;
	int				draw_start;
	int				draw_end;
	double			step;
	double			tex_pos;

	choose_text(&text, d, ray);
	draw_start = -(WINDOW_H / ray.distance) / 2 + WINDOW_H / 2.0;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = (WINDOW_H / ray.distance) / 2 + WINDOW_H / 2.0;
	if (draw_end >= WINDOW_H)
		draw_end = WINDOW_H - 1;
	step = 1.0 * text.height / (WINDOW_H / ray.distance);
	tex_pos = (draw_start - WINDOW_H / 2.0
			+ (WINDOW_H / ray.distance) / 2.0) * step;
	while (draw_start < draw_end)
	{
		draw_wide_pixel(d, ray_number, draw_start, color(text, ray, tex_pos));
		tex_pos += step;
		draw_start++;
	}
}

void	draw_vertical(t_data d, int ray_number, int w, int h)
{
	int	x;
	int	y;
	int	coord_y;

	x = 0;
	coord_y = (WINDOW_H / 2) - (h / 2);
	while (x < w)
	{
		y = 0;
		while (y < h)
		{
			image_pixel_put(d, ray_number + x, coord_y + y,
				0xFF00FF00);
			y++;
		}
		x++;
	}
}
