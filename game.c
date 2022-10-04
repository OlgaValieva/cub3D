/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carys <carys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 10:51:32 by carys             #+#    #+#             */
/*   Updated: 2022/10/04 20:21:54 by carys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void start_game(t_game *game)
{
    find_position(game);
    game->mlx = mlx_init();
    bonus_map_init_picture(game);
    ft_resoures_init(game);
    game->win = mlx_new_window(game->mlx, WINDOW_W, WINDOW_H, "cub3d");
    ft_redraw(game);
    mlx_hook(game->win, ON_KEYDOWN, KeyPressMask, ft_key, game);
    mlx_hook(game->win, ON_DESTROY, NoEventMask, ft_destroy_exit, game);
    mlx_loop(game->mlx);
}