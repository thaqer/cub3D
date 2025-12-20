/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaniatt <tbaniatt@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-27 13:54:18 by tbaniatt          #+#    #+#             */
/*   Updated: 2025-11-27 13:54:18 by tbaniatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	check_corner(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = 0;
	map_y = 0;
	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_y < 0)
		return (0);
	if (!game->map->map[map_y] || !game->map->map[map_y][map_x])
		return (0);
	if (game->map->map[map_y][map_x] == '1'
		|| game->map->map[map_y][map_x] == ' ')
		return (0);
	return (1);
}

/* we check all four corners of the player rectangle
   to avoid going through walls*/
/* margin is a small value to ensure we are slightly inside the walkable area */
static int	check_valid_move(t_game *game, double new_x, double new_y)
{
	double	margin;
	int		i;
	double	corners_x[4];
	double	corners_y[4];

	margin = 0.04;
	corners_x[0] = new_x + margin;
	corners_y[0] = new_y + margin;
	corners_x[1] = new_x - margin;
	corners_y[1] = new_y + margin;
	corners_x[2] = new_x + margin;
	corners_y[2] = new_y - margin;
	corners_x[3] = new_x - margin;
	corners_y[3] = new_y - margin;
	i = 0;
	while (i < 4)
	{
		if (!check_corner(game, corners_x[i], corners_y[i]))
			return (0);
		i++;
	}
	return (1);
}

/* This function handles collision detection with wall sliding
 ** If diagonal movement is blocked, it tries moving along each axis separately
 ** This allows the player to "slide" along walls instead of getting stuck */
void	handle_sliding_move(t_game *game, double new_x, double new_y)
{
	double	current_x;
	double	current_y;

	current_x = game->player->x;
	current_y = game->player->y;
	if (check_valid_move(game, new_x, new_y))
	{
		game->player->x = new_x;
		game->player->y = new_y;
		return ;
	}
	if (check_valid_move(game, new_x, current_y))
	{
		game->player->x = new_x;
		return ;
	}
	if (check_valid_move(game, current_x, new_y))
	{
		game->player->y = new_y;
		return ;
	}
}
