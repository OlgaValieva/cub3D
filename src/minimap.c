/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carys <carys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:05:44 by carys             #+#    #+#             */
/*   Updated: 2022/10/04 15:07:48 by carys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "..cub3d.h"

void	draw(t_data d, t_coord pos_i, unsigned int unit,
			unsigned int color)
{
	t_size	unit_pos;
	t_size	index;

	unit_pos.x = pos_i.x * unit;
	unit_pos.y = pos_i.y * unit;
	index.x = unit_pos.x;
	while (index.x < unit_pos.x + unit)
	{
		index.y = unit_pos.y;
		while (index.y < unit_pos.y + unit)
		{
			image_pixel_put(d, index.x, index.y, color);
			index.y++;
		}
		index.x++;
	}
}

void	draw_mini_wall(t_data d, t_coord pos_i, unsigned int unit)
{
	if (d.map[pos_i.y][pos_i.x] == '1')
		draw(d, pos_i, unit, 0xF48395A);
	else if (d.map[pos_i.y][pos_i.x] == '0')
		draw(d, pos_i, unit, 0xFA9A9A9);
}

void	draw_minimap(t_data d)
{
	unsigned int	unit;
	t_coord			pos_i;
	t_coord			player;
	size_t			len;

	if (WINDOW_H * MINIMAP_SIZE / d.size_y < WINDOW_W * MINIMAP_SIZE / d.size_x)
		unit = WINDOW_H * MINIMAP_SIZE / d.size_y;
	else
		unit = WINDOW_W * MINIMAP_SIZE / d.size_x;
	pos_i.y = 0;
	while ((size_t)pos_i.y < d.size_y)
	{
		pos_i.x = 0;
		len = ft_strlen(d.map[pos_i.y]);
		while ((size_t)pos_i.x < len)
		{
			draw_mini_wall(d, pos_i, unit);
			pos_i.x++;
		}
		pos_i.y++;
	}
	player.x = d.player_x;
	player.y = d.player_y;
	draw(d, player, unit, 0xFDA70D6);
}

void	ft_perror(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	ft_error(char *str)
{
	if (str)
		ft_putstr_fd(str, 2);
	exit(1);
}


