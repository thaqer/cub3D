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
	game->images = malloc(sizeof(t_images));
	if (!game->images)
	{
		error_exit(game, "Error: Failed to allocate memory for images\n");
		return (NULL);
	}
	init_map_struct(game->map);
	init_flags_struct(game->flags);
	init_textures_struct(game->textures);
	if (parse_map(map_path, game) == -1)
	{
		error_exit(game, "Error: Failed to parse map\n");
		return (NULL);
	}
	///////debugging
	print_game_info(game);
	// test_mlx_functions(game);
	return (game);
}
