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

int	init_game(char *map_path)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (-1);
	game->map = malloc(sizeof(t_map));
	if (!game->map)
		return (-1);
	game->flags = malloc(sizeof(t_flags));
	if (!game->flags)
		return (-1);
	game->textures = malloc(sizeof(t_textures));
	if (!game->textures)
		return (-1);
	if (parse_map(map_path, game) == -1)
		return (-1);
	return (0);
}