/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dqaddomi <dqaddomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 18:13:45 by tbaniatt          #+#    #+#             */
/*   Updated: 2025/11/25 19:05:00 by tbaniatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	load_images(t_game *game)
{
	game->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D", false);
	if (!game->mlx)
		return (error_exit(game, "Error\nFailed to initialize MLX\n"));
	game->img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->img)
		return (error_exit(game, "Error\nFailed to create image\n"));
	game->textures->north = mlx_load_png(game->map->north);
	if (!game->textures->north)
		return (error_exit(game, "Error\nFailed to load north texture\n"));
	game->textures->south = mlx_load_png(game->map->south);
	if (!game->textures->south)
		return (error_exit(game, "Error\nFailed to load south texture\n"));
	game->textures->west = mlx_load_png(game->map->west);
	if (!game->textures->west)
		return (error_exit(game, "Error\nFailed to load west texture\n"));
	game->textures->east = mlx_load_png(game->map->east);
	if (!game->textures->east)
		return (error_exit(game, "Error\nFailed to load east texture\n"));
	game->textures->cloud = mlx_load_png("./textures/cloudst.png");
	if (!game->textures->cloud)
		return (error_exit(game, "Error\nFailed to load cloud texture\n"));
	return (1);
}

void	draw_floor_ceiling(t_game *game)
{
	int		x;
	int		y;
	double	angle;

	angle = atan2(game->player->dir_y, game->player->dir_x);
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			if (y < WINDOW_HEIGHT / 2)
			{
				mlx_put_pixel(game->img, x, y, game->ceiling_color);
				draw_textured_ceiling(game, x, y, angle);
			}
			else
				mlx_put_pixel(game->img, x, y, game->floor_color);
			x++;
		}
		y++;
	}
}

int	run_game(t_game *game)
{
	if (load_images(game) != 1)
		return (-1);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	init_mouse(game);
	mlx_loop_hook(game->mlx, &game_loop, game);
	mlx_loop(game->mlx);
	free_game(game);
	return (EXIT_SUCCESS);
}
