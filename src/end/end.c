/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniah <daniah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 12:25:26 by tbaniatt          #+#    #+#             */
/*   Updated: 2025/12/11 20:45:03 by daniah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_textures(t_textures *textures)
{
	if (textures)
	{
		if (textures->north)
			mlx_delete_texture(textures->north);
		if (textures->south)
			mlx_delete_texture(textures->south);
		if (textures->west)
			mlx_delete_texture(textures->west);
		if (textures->east)
			mlx_delete_texture(textures->east);
		if (textures->cloud)
			mlx_delete_texture(textures->cloud);
		free(textures);
	}
}

static void	map_free(t_map *map)
{
	size_t	i;

	if (!map || !map->map)
		return ;
	i = 0;
	while (map->map[i])
	{
		free(map->map[i]);
		map->map[i] = NULL;
		i++;
	}
	free(map->map);
	map->map = NULL;
}

void	free_map(t_map *map)
{
	if (!map)
		return ;
	if (map->north)
		free(map->north);
	if (map->south)
		free(map->south);
	if (map->west)
		free(map->west);
	if (map->east)
		free(map->east);
	if (map->floor)
		free(map->floor);
	if (map->ceiling)
		free(map->ceiling);
	map_free(map);
	free(map);
}

void	free_game(t_game *game)
{
	if (!game)
		return ;
	if (game->map)
		free_map(game->map);
	if (game->textures)
		free_textures(game->textures);
	if (game->flags)
		free(game->flags);
	if (game->player)
		free(game->player);
	if (game->img && game->mlx)
		mlx_delete_image(game->mlx, game->img);
	if (game->mlx)
		mlx_terminate(game->mlx);
	free(game);
}

int	error_exit(t_game *game, char *message)
{
	if (message)
		ft_putstr_fd(message, 2);
	free_game(game);
	return (-1);
}
