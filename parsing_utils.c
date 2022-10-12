/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:03:47 by carys             #+#    #+#             */
/*   Updated: 2022/10/12 16:13:33 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	image_pixel_put(t_data d, int x, int y, unsigned int color)
{
	int		*img_addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;

	img_addr = (int *)mlx_get_data_addr(d.img, &bits_per_pixel, &size_line,
			&endian);
	if (x < 0 || x >= WINDOW_W)
		return ;
	if (y < 0 || y >= WINDOW_H)
		return ;
	color = mlx_get_color_value(d.mlx, color);
	img_addr[y * WINDOW_W + x] = color;
}

/*
Проверка на новую/пустую строку в середине карты
взводится флаг *newline для новой строки
Определяем размеры карты d->size_x и d->size_y
*/
void	check_newline(char *str, t_data *d, int *newline)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '\0')
		(*newline) = 1;
	else
	{
		if ((*newline) == 1)
		{
			free(str);
			ft_error("cub3d: empty line\n");
		}
		else
		{
			if ((size_t)ft_strlen(str) > d->size_x)
				d->size_x = ft_strlen(str);
			d->size_y++;
		}
	}
	free(str);
}

/*
Считаем, что считанная строка относится к карте.
Определяем размеры карты d->size_x и d->size_y
*/
int	get_x_y(char *str, t_data *d, int fd)
{
	int	newline;

	newline = 0;
	check_newline(str, d, &newline);
	while (ft_gnl(&str, fd))
		check_newline(str, d, &newline);
	check_newline(str, d, &newline);
	return (0);
}

void	get_map(t_data *d, char *filename)
{
	int		fd;
	size_t	i;

	if (d->size_y == 0)
		return ;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		ft_perror("Cub3d: file open error      ");
	d->map = (char **)malloc(sizeof(char *) * (d->size_y + 1));
	if (!d->map)
		ft_error("Cub3d: error: unable to allocate memory!\n");
	i = 0;
	while (ft_gnl(&d->map[i], fd) && d->skip > 0)
	{
		d->skip--;
		free(d->map[i]);
	}
	i++;
	while (ft_gnl(&d->map[i], fd) && i < d->size_y - 1)
		i++;
	d->map[++i] = NULL;
	close(fd);
}

void	check_data(t_data *d)
{
	if (!d->map)
		error_free("Cub3d: missing map!\n", d);
	if (!d->north_texture.filename)
		error_free("cub3d: missing north texture\n", d);
	if (!d->south_texture.filename)
		error_free("cub3d: missing south texture\n", d);
	if (!d->west_texture.filename)
		error_free("cub3d: missing west texture\n", d);
	if (!d->east_texture.filename)
		error_free("cub3d: missing east texture\n", d);
	if (d->f_color == -1)
		error_free("cub3d: missing floor color\n", d);
	if (d->c_color == -1)
		error_free("cub3d: missing ceilling color\n", d);
}
