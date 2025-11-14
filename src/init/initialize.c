/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaniatt <tbaniatt@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 09:16:39 by tbaniatt          #+#    #+#             */
/*   Updated: 2025/11/15 00:12:31 by tbaniatt         ###   ########.fr       */
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

	game = malloc(sizeof(t_game));
	if (!game)
	{
		error_exit(NULL, "Error: Failed to allocate memory for game\n");
		return (NULL);
	}
	game->mlx = NULL;
	game->map = malloc(sizeof(t_map));
	if (!game->map)
	{
		error_exit(game, "Error: Failed to allocate memory for map\n");
		return (NULL);
	}
	game->flags = malloc(sizeof(t_flags));
	if (!game->flags)
	{
		error_exit(game, "Error: Failed to allocate memory for flags\n");
		return (NULL);
	}
	game->textures = malloc(sizeof(t_textures));
	if (!game->textures)
	{
		error_exit(game, "Error: Failed to allocate memory for textures\n");
		return (NULL);
	}
	game->player = malloc(sizeof(t_player));
	if (!game->player)
	{
		error_exit(game, "Error: Failed to allocate memory for player\n");
		return (NULL);
	}
	init_map_struct(game->map);
	init_flags_struct(game->flags);
	init_textures_struct(game->textures);
	game->img = NULL;
	game->floor_color = 0;
	game->ceiling_color = 0;
	if (parse_map(map_path, game) == -1)
	{
		error_exit(game, "Error: Failed to parse map\n");
		return (NULL);
	}
	init_player(game);
	///////debugging
	print_game_info(game);
	// test_mlx_functions(game);
	return (game);
}

void	init_player(t_game *game)
{
	int		i, j;
	char	player_dir = 0;

	i = 0;
	while (game->map->map[i])
	{
		j = 0;
		while (game->map->map[i][j])
		{
			if (game->map->map[i][j] == 'N' || game->map->map[i][j] == 'S' ||
				game->map->map[i][j] == 'E' || game->map->map[i][j] == 'W')
			{
				game->player->x = j + 0.5;
				game->player->y = i + 0.5;
				player_dir = game->map->map[i][j];
				game->map->map[i][j] = '0';
				break;
			}
			j++;
		}
		if (player_dir)
			break;
		i++;
	}
	// Set player direction
	if (player_dir == 'N')
	{
		game->player->dir_x = 0;
		game->player->dir_y = -1;
		game->player->plane_x = 0.66;
		game->player->plane_y = 0;
	}
	else if (player_dir == 'S')
	{
		game->player->dir_x = 0;
		game->player->dir_y = 1;
		game->player->plane_x = -0.66;
		game->player->plane_y = 0;
	}
	else if (player_dir == 'E')
	{
		game->player->dir_x = 1;
		game->player->dir_y = 0;
		game->player->plane_x = 0;
		game->player->plane_y = 0.66;
	}
	else if (player_dir == 'W')
	{
		game->player->dir_x = -1;
		game->player->dir_y = 0;
		game->player->plane_x = 0;
		game->player->plane_y = -0.66;
	}
}
