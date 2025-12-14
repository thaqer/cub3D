/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dqaddomi <dqaddomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 23:33:03 by daniah            #+#    #+#             */
/*   Updated: 2025/11/25 18:39:08 by dqaddomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	rotate_camera(t_game *game, double angle)
{
	double	prev_dir_x;
	double	prev_plane_x;

	prev_dir_x = game->player->dir_x;
	game->player->dir_x = game->player->dir_x * cos(angle) - game->player->dir_y
		* sin(angle);
	game->player->dir_y = prev_dir_x * sin(angle) + game->player->dir_y
		* cos(angle);
	prev_plane_x = game->player->plane_x;
	game->player->plane_x = game->player->plane_x * cos(angle)
		- game->player->plane_y * sin(angle);
	game->player->plane_y = prev_plane_x * sin(angle) + game->player->plane_y
		* cos(angle);
}

void	handle_mouse_move(double x_pos, double y_pos, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	game->mouse_dx += x_pos - game->mouse_x;
	game->mouse_x = x_pos;
	(void)y_pos;
}

void	handle_mouse_rotation(t_game *game)
{
	double	rotation;
	double	sensitivity;

	sensitivity = 0.001;
	rotation = game->mouse_dx * sensitivity;
	game->mouse_dx *= 0.5;
	if (fabs(rotation) > 0.0001)
		rotate_camera(game, rotation);
}

void	init_mouse(t_game *game)
{
	int32_t	mouse_x;
	int32_t	mouse_y;

	mlx_get_mouse_pos(game->mlx, &mouse_x, &mouse_y);
	game->mouse_x = (double)mouse_x;
	game->mouse_y = (double)mouse_y;
	game->mouse_dx = 0.0;
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
	mlx_cursor_hook(game->mlx, &handle_mouse_move, game);
}
