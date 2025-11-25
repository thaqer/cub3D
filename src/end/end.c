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

	if (map)
	{
		if (map->north)
			free(map->north);
		if (map->south)
			free(map->south);
		if (map->west)
			free(map->west);
		if (map->east)
			free(map->east);
		if (map->map)
		{
			i = 0;
			while (map->map[i])
				free(map->map[i++]);
			free(map->map);
		}
		free(map);
	}
}

void	free_game(t_game *game)
{
	if (game)
	{
		free_map(game->map);
		free_textures(game->textures);
		free_flags(game->flags);
		if (game->player)
			free(game->player);
		if (game->img && game->mlx)
			mlx_delete_image(game->mlx, game->img);
		if (game->mlx)
			mlx_terminate(game->mlx);
		free(game);
	}
}

int	error_exit(t_game *game, char *message)
{
	if (message)
		ft_putstr_fd(message, 2);
	free_game(game);
	return (-1);
}
