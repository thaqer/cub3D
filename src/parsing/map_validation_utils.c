/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dqaddomi <dqaddomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 13:46:16 by tbaniatt          #+#    #+#             */
/*   Updated: 2025/12/23 15:54:21 by dqaddomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_map_char(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map->map[i])
	{
		j = 0;
		while (game->map->map[i][j])
		{
			if (!valid_map_char(game->map->map[i][j]))
			{
				error_exit(game, "Error: Invalid char in map\n");
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	players(t_game *game, int *player_x, int *player_y)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (game->map->map[i])
	{
		j = 0;
		while (game->map->map[i][j])
		{
			if (game->map->map[i][j] == 'N' || game->map->map[i][j] == 'W'
				|| game->map->map[i][j] == 'S' || game->map->map[i][j] == 'E')
			{
				*player_x = j;
				*player_y = i;
				count++;
			}
			j++;
		}
		i++;
	}
	return (count);
}

int	is_valid_neighbor(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}
