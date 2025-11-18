/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_validation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dqaddomi <dqaddomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:33:42 by dqaddomi          #+#    #+#             */
/*   Updated: 2025/11/18 14:04:50 by dqaddomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	is_png(char *path)
{
	int	len;

	if (!path)
		return (0);
	len = ft_strlen(path);
	if (len < 4)
		return (0);
	if (ft_strncmp(path + len - 4, ".png", 4) == 0)
		return (1);
	return (0);
}

static int	validate_texture(char *path)
{
	int	fd;

	if (!path)
		return (0);
	if (!is_png(path))
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	check_textures(t_game *game)
{
	if (!validate_texture(game->map->north))
	{
		error_exit(game, "Error: Invalid north texture path\n");
		return (-1);
	}
	if (!validate_texture(game->map->south))
	{
		error_exit(game, "Error: Invalid south texture path\n");
		return (-1);
	}
	if (!validate_texture(game->map->west))
	{
		error_exit(game, "Error: Invalid west texture path\n");
		return (-1);
	}
	if (!validate_texture(game->map->east))
	{
		error_exit(game, "Error: Invalid east texture path\n");
		return (-1);
	}
	return (0);
}
