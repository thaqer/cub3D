/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaniatt <tbaniatt@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-11 18:13:45 by tbaniatt          #+#    #+#             */
/*   Updated: 2025-11-11 18:13:45 by tbaniatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int run_game(t_game *game)
{
	// Game loop and rendering logic would go here
	game->mlx = mlx_init(800, 600, "Cub3D", true);
	if (!game->mlx)
		return (-1);
	// Additional setup like loading textures, setting up the scene, etc.

	mlx_loop(game->mlx);
	return (0);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
	// Additional key handling logic
}