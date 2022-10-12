/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carys <carys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:56:43 by carys             #+#    #+#             */
/*   Updated: 2022/10/12 11:17:57 by carys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_vertical(t_data *d, int y)
{
	int	x;

	x = 0;
	while (ft_isspace(d->map[y][x]))
		x++;
	if (d->map[y][x] && d->map[y][x] != '1')
		error_free("cub3d: map is not surrounded by walls from the west\n", d);
	while (d->map[y][x])
		x++;
	x--;
	while (x > 0 && ft_isspace(d->map[y][x]))
		x--;
	if (d->map[y][x] && d->map[y][x] != '1')
		error_free("cub3d: map is not surrounded by walls from the east\n", d);
}

void	check_walls(t_data *d, size_t x, size_t y)
{
	size_t	len;

	while (y < d->size_y)
	{
		check_vertical(d, y);
		x = 0;
		len = ft_strlen(d->map[y]);
		while (y == 0 && x < len)
		{
			if (d->map[0][x] && d->map[0][x] != '1'
				&& !ft_isspace(d->map[0][x]))
				error_free("isn't surrounded by walls from the north\n", d);
			x++;
		}
		len = ft_strlen(d->map[y]);
		while (y == d->size_y - 1 && x < len)
		{
			if (d->map[d->size_y - 1][x] && d->map[d->size_y - 1][x] != '1'
				&& !ft_isspace(d->map[d->size_y - 1][x]))
				error_free("isn't surrounded by walls from the south\n", d);
			x++;
		}
		y++;
	}
}

void	save_player_data(t_data *d, char c, int x, int y)
{
	d->map[y][x] = '0';
	d->player_x = x + 0.5;
	d->player_y = y + 0.5;
	if (c == 'N')
		d->view_angle = 0;
	else if (c == 'E')
		d->view_angle = 90;
	else if (c == 'S')
		d->view_angle = 180;
	else if (c == 'W')
		d->view_angle = 270;
}

void	check_forbidden_char(t_data *d, size_t x, size_t y)
{
	int		player;
	size_t	len;

	player = 0;
	while (y < d->size_y)
	{
		x = 0;
		len = ft_strlen(d->map[y]);
		while (x < len)
		{
			if (!(ft_strchr("NSWE01 ", d->map[y][x])))
				error_free("cub3d: forbidden character is used!\n", d);
			if (ft_strchr("NSWE", d->map[y][x]))
			{
				save_player_data(d, d->map[y][x], x, y);
				player++;
			}
			x++;
		}
		y++;
	}
	if (player != 1)
		error_free("cub3d: wrong count of players\n", d);
}

void	check_space(t_data *d, size_t x, size_t y)
{
	size_t	len;

	while (y < d->size_y)
	{
		x = 0;
		len = ft_strlen(d->map[y]);
		while (x < len)
		{
			if ((d->map[y][x]) != '1' && !ft_isspace(d->map[y][x]))
			{
				if ((x - 1 >= 0 && ft_isspace(d->map[y][x - 1]))
				|| (x + 1 < (size_t)ft_strlen(d->map[y])
					&& ft_isspace(d->map[y][x + 1]))
					|| (y + 1 < d->size_y && ft_isspace(d->map[y + 1][x]))
					|| (y - 1 >= 0 && ft_isspace(d->map[y - 1][x])))
					error_free("cub3d: space isn't surrounded by walls\n", d);
			}
			x++;
		}
		y++;
	}
}
