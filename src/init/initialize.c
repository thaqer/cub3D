/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaniatt <tbaniatt@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-31 09:16:39 by tbaniatt          #+#    #+#             */
/*   Updated: 2025-10-31 09:16:39 by tbaniatt         ###   ########.fr       */
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
	textures->no = NULL;
	textures->so = NULL;
	textures->we = NULL;
	textures->ea = NULL;
}

int	init_game(char *map_path)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (-1);
	game->mlx = NULL;
	game->window = NULL;
	game->map = malloc(sizeof(t_map));
	if (!game->map)
		return (free(game), -1);
	game->flags = malloc(sizeof(t_flags));
	if (!game->flags)
		return (free(game->map), free(game), -1);
	game->textures = malloc(sizeof(t_textures));
	if (!game->textures)
		return (free(game->flags), free(game->map), free(game), -1);
	init_map_struct(game->map);
	init_flags_struct(game->flags);
	init_textures_struct(game->textures);
	if (parse_map(map_path, game) == -1)
		return (-1);
	///////debugging
	print_game_info(game);
	return (0);
}
