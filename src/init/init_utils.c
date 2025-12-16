/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniah <daniah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 16:50:19 by tbaniatt          #+#    #+#             */
/*   Updated: 2025/12/11 20:16:30 by daniah           ###   ########.fr       */
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
	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		return (error_init(NULL, "Error: allocate memory for game\n"));
	game->map = ft_calloc(1, sizeof(t_map));
	if (!game->map)
		return (error_init(game, "Error: allocate memory for map\n"));
	game->flags = ft_calloc(1, sizeof(t_flags));
	if (!game->flags)
		return (error_init(game, "Error: allocate memory for flags\n"));
	game->textures = ft_calloc(1, sizeof(t_textures));
	if (!game->textures)
		return (error_init(game, "Error: allocate memory for textures\n"));
	game->player = ft_calloc(1, sizeof(t_player));
	if (!game->player)
		return (error_init(game, "Error: allocate memory for player\n"));
	return (game);
}

void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	init_map_struct(t_map *map)
{
	map->north = NULL;
	map->south = NULL;
	map->west = NULL;
	map->east = NULL;
	map->floor = NULL;
	map->ceiling = NULL;
	map->map = NULL;
}

void	init_flags_struct(t_flags *flags)
{
	flags->wall_north = 0;
	flags->wall_south = 0;
	flags->wall_west = 0;
	flags->wall_east = 0;
	flags->floor = 0;
	flags->ceiling = 0;
	flags->map = 0;
}
