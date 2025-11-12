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
	game->mlx = mlx_init(800, 600, "Cub3D", false);
	if (!game->mlx)
		return (error_exit(game, "Error: Failed to initialize MLX\n"));
	mlx_key_hook(game->mlx, &key_hook, game);
	game->textures->north = mlx_load_png(game->map->north);
	if (game->textures->north == NULL)
		return (error_exit(game, "Error: Failed to load north texture\n"));
	game->images->north = mlx_texture_to_image(game->mlx, game->textures->north);
	if (game->images->north == NULL)
		return (error_exit(game, "Error: Failed to convert north texture to image\n"));
	mlx_image_to_window(game->mlx, game->images->north, 0, 0);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (EXIT_SUCCESS);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		{
			mlx_close_window(game->mlx);
			free_game(game);
		}
	// Additional key handling logic
}