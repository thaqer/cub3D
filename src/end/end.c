/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dqaddomi <dqaddomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 12:25:26 by tbaniatt          #+#    #+#             */
/*   Updated: 2025/11/25 19:43:33 by dqaddomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_flags(t_flags *flags)
{
	if (flags)
		free(flags);
}

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

void	free_map(t_map *map)
{
	size_t	i;

	if (!map)
		return ;
	if (map->north)
	{
		free(map->north);
		map->north = NULL;
	}
	if (map->south)
	{
		free(map->south);
		map->south = NULL;
	}
	if (map->west)
	{
		free(map->west);
		map->west = NULL;
	}
	if (map->east)
	{
		free(map->east);
		map->east = NULL;
	}
	if (map->map)
	{
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
	free(map);
}

void	free_game(t_game *game)
{
	if (!game)
		return ;
	if (game->map)
	{
		free_map(game->map);
		game->map = NULL;
	}
	if (game->textures)
	{
		free_textures(game->textures);
		game->textures = NULL;
	}
	if (game->flags)
	{
		free_flags(game->flags);
		game->flags = NULL;
	}
	if (game->player)
	{
		free(game->player);
		game->player = NULL;
	}
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
