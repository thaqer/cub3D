/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dqaddomi <dqaddomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 19:55:36 by dqaddomi          #+#    #+#             */
/*   Updated: 2025/11/24 10:39:13 by dqaddomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	check_map_char(t_game *game)
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

static int	players(t_game *game, int *player_x, int *player_y)
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

static int	is_correct_position(t_game *game, int x, int y)
{
	int	total_rows;
	int	row_len;

	total_rows = 0;
	while (game->map->map[total_rows])
		total_rows++;
	if (y == 0 || y == total_rows - 1)
		return (0);
	row_len = ft_strlen(game->map->map[y]);
	if (x == 0 || x == row_len - 1)
		return (0);
	if (y > 0 && (x >= (int)ft_strlen(game->map->map[y - 1])
			|| game->map->map[y - 1][x] == ' '))
		return (0);
	if (y < total_rows - 1 && (x >= (int)ft_strlen(game->map->map[y + 1])
			|| game->map->map[y + 1][x] == ' '))
		return (0);
	if (x > 0 && game->map->map[y][x - 1] == ' ')
		return (0);
	if (x < row_len - 1 && game->map->map[y][x + 1] == ' ')
		return (0);
	return (1);
}

static int	check_walls_enclosed(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map->map[i])
	{
		j = 0;
		while (game->map->map[i][j])
		{
			if (game->map->map[i][j] == '0' || game->map->map[i][j] == 'N'
				|| game->map->map[i][j] == 'S' || game->map->map[i][j] == 'E'
				|| game->map->map[i][j] == 'W')
			{
				if (!is_correct_position(game, j, i))
				{
					error_exit(game, "Error: Map not enclosed by walls\n");
					return (-1);
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	validate_map(t_game *game)
{
	int	player_x;
	int	player_y;
	int	player_count;

	player_x = 0;
	player_y = 0;
	if (check_map_char(game) == -1)
		return (-1);
	player_count = players(game, &player_x, &player_y);
	if (player_count != 1)
	{
		error_exit(game, "Error: Map must have exactly one player\n");
		return (-1);
	}
	if (check_walls_enclosed(game) == -1)
		return (-1);
	return (0);
}
