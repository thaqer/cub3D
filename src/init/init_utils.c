/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaniatt <tbaniatt@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-15 16:50:19 by tbaniatt          #+#    #+#             */
/*   Updated: 2025-11-15 16:50:19 by tbaniatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static t_game	*error_init(t_game *game, const char *message)
{
	error_exit(game, (char *)message);
	return (NULL);
}

t_game	*malloc_init(t_game *game)
{
	game = malloc(sizeof(t_game));
	if (!game)
		return (error_init(NULL, "Error: allocate memory for game\n"));
	game->mlx = NULL;
	game->map = malloc(sizeof(t_map));
	if (!game->map)
		return (error_init(game, "Error: allocate memory for map\n"));
	game->flags = malloc(sizeof(t_flags));
	if (!game->flags)
		return (error_init(game, "Error: allocate memory for flags\n"));
	game->textures = malloc(sizeof(t_textures));
	if (!game->textures)
		return (error_init(game, "Error: allocate memory for textures\n"));
	game->player = malloc(sizeof(t_player));
	if (!game->player)
		return (error_init(game, "Error: allocate memory for player\n"));
	return (game);
}
