/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaniatt <tbaniatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 16:26:48 by tbaniatt          #+#    #+#             */
/*   Updated: 2025/11/26 19:02:04 by tbaniatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	handle_player_movement_util(t_game *game, double move_speed
		, double *new_x, double *new_y)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		*new_x = game->player->x + game->player->dir_x * move_speed;
		*new_y = game->player->y + game->player->dir_y * move_speed;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		*new_x = game->player->x - game->player->dir_x * move_speed;
		*new_y = game->player->y - game->player->dir_y * move_speed;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		*new_x = game->player->x - game->player->dir_y * move_speed;
		*new_y = game->player->y + game->player->dir_x * move_speed;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		*new_x = game->player->x + game->player->dir_y * move_speed;
		*new_y = game->player->y - game->player->dir_x * move_speed;
	}
}

static void	handle_player_movement(t_game *game)
{
	double	move_speed;
	double	new_x;
	double	new_y;

	move_speed = 0.05;
	new_x = 0;
	new_y = 0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT_SHIFT)
		|| mlx_is_key_down(game->mlx, MLX_KEY_RIGHT_SHIFT))
		move_speed *= 2;
	handle_player_movement_util(game, move_speed, &new_x, &new_y);
	handle_sliding_move(game, new_x, new_y);
}

static void	rotate_player(t_game *game, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player->dir_x;
	game->player->dir_x = game->player->dir_x * cos(rot_speed)
		- game->player->dir_y * sin(rot_speed);
	game->player->dir_y = old_dir_x * sin(rot_speed) + game->player->dir_y
		* cos(rot_speed);
	old_plane_x = game->player->plane_x;
	game->player->plane_x = game->player->plane_x * cos(rot_speed)
		- game->player->plane_y * sin(rot_speed);
	game->player->plane_y = old_plane_x * sin(rot_speed) + game->player->plane_y
		* cos(rot_speed);
}

void	handle_movement(t_game *game)
{
	double	rot_speed;

	handle_player_movement(game);
	rot_speed = 0.03;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_player(game, rot_speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_player(game, -rot_speed);
}

void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	handle_mouse_rotation(game);
	handle_movement(game);
	cast_rays(param);
}
