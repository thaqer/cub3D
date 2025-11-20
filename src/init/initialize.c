/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dqaddomi <dqaddomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 09:16:39 by tbaniatt          #+#    #+#             */
/*   Updated: 2025/11/20 14:45:21 by dqaddomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_map_struct(t_map *map)
{
	map->north = NULL;
	map->south = NULL;
	map->west = NULL;
	map->east = NULL;
	map->floor[0] = '\0';
	map->ceiling[0] = '\0';
	map->map = NULL;
}

static void	init_flags_struct(t_flags *flags)
{
	flags->wall_north = 0;
	flags->wall_south = 0;
	flags->wall_west = 0;
	flags->wall_east = 0;
	flags->floor = 0;
	flags->ceiling = 0;
	flags->map = 0;
}

static void	init_textures_struct(t_textures *textures)
{
	textures->north = NULL;
	textures->south = NULL;
	textures->west = NULL;
	textures->east = NULL;
}

t_game	*init_game(char *map_path)
{
	t_game	*game;
	t_game	*temp;

	temp = NULL;
	game = malloc_init(temp);
	if (!game)
		return (NULL);
	init_map_struct(game->map);
	init_flags_struct(game->flags);
	init_textures_struct(game->textures);
	game->img = NULL;
	game->floor_color = 0;
	game->ceiling_color = 0;
	if (parse_map(map_path, game) == -1)
	{
		error_exit(game, "Error: Failed to parse map configuration\n");
		return (NULL);
	}
	if (parse_map_grid(map_path, game) == -1)
	{
		error_exit(game, "Error: Failed to parse map grid\n");
		return (NULL);
	}
	parse_color(game->map->floor, &game->floor_color);
	parse_color(game->map->ceiling, &game->ceiling_color);
	if (check_textures(game) == -1)
		return (NULL);
	if (validate_map(game) == -1)
		return (NULL);
	init_player(game);
	print_game_info(game);
	return (game);
}

static void	player_direction(t_game *game, char player_dir)
{
	game->player->dir_x = 0;
	game->player->dir_y = 0;
	game->player->plane_x = 0;
	game->player->plane_y = 0;
	if (player_dir == 'N')
	{
		game->player->dir_y = -1;
		game->player->plane_x = 0.72;
	}
	else if (player_dir == 'S')
	{
		game->player->dir_y = 1;
		game->player->plane_x = -0.72;
	}
	else if (player_dir == 'E')
	{
		game->player->dir_x = 1;
		game->player->plane_y = 0.72;
	}
	else if (player_dir == 'W')
	{
		game->player->dir_x = -1;
		game->player->plane_y = -0.72;
	}
}

void	init_player(t_game *game)
{
	int		i;
	int		j;
	char	player_dir;

	i = -1;
	player_dir = 0;
	while (game->map->map[++i])
	{
		j = -1;
		while (game->map->map[i][++j])
		{
			if (game->map->map[i][j] == 'N' || game->map->map[i][j] == 'S' ||
				game->map->map[i][j] == 'E' || game->map->map[i][j] == 'W')
			{
				game->player->x = j + 0.5;
				game->player->y = i + 0.5;
				player_dir = game->map->map[i][j];
				game->map->map[i][j] = '0';
				break ;
			}
		}
		if (player_dir)
			break ;
	}
	player_direction(game, player_dir);
}
