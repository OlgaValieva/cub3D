/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carys <carys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:13:39 by carys             #+#    #+#             */
/*   Updated: 2022/10/12 11:18:11 by carys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_end(t_data *d)
{
	mlx_destroy_image(d->mlx, d->north_texture.mlx_img_ptr);
	mlx_destroy_image(d->mlx, d->west_texture.mlx_img_ptr);
	mlx_destroy_image(d->mlx, d->south_texture.mlx_img_ptr);
	mlx_destroy_image(d->mlx, d->east_texture.mlx_img_ptr);
	mlx_destroy_window(d->mlx, d->mlx_win);
	free(d->mlx);
	all_free(d);
	exit(0);
}

static void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

void	free_texture(t_texture tex)
{
	if (tex.filename)
		free(tex.filename);
}

void	error_free(char *str, t_data *d)
{
	all_free(d);
	printf(COLOR"Error\n");
	if (str)
		ft_putstr_fd(str, 2);
	exit(1);
}

void	all_free(t_data *d)
{
	free_texture(d->east_texture);
	free_texture(d->west_texture);
	free_texture(d->north_texture);
	free_texture(d->south_texture);
	if (d->map)
		ft_free(d->map);
}
