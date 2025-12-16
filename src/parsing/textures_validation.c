/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_validation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dqaddomi <dqaddomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:33:42 by dqaddomi          #+#    #+#             */
/*   Updated: 2025/11/25 21:25:00 by dqaddomi         ###   ########.fr       */
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
		return (3);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	check_textures(t_game *game)
{
	if (!validate_texture(game->map->north))
		return (error_exit(NULL, "Error: Invalid north texture path\n"));
	else if (validate_texture(game->map->north) == 3)
		return (error_exit(NULL,"Error: North texture is not a .png file\n"));
	if (!validate_texture(game->map->south))
		return (error_exit(NULL, "Error: Invalid south texture path\n"));
	else if (validate_texture(game->map->south) == 3)
		return (error_exit(NULL, "Error: South texture is not a .png file\n"));
	if (!validate_texture(game->map->west))
		return (error_exit(NULL, "Error: Invalid west texture path\n"));
	else if (validate_texture(game->map->west) == 3)
		return (error_exit(NULL, "Error: West texture is not a .png file\n"));
	if (!validate_texture(game->map->east))
		return (error_exit(NULL, "Error: Invalid east texture path\n"));
	else if (validate_texture(game->map->east) == 3)
		return (error_exit(NULL, "Error: East texture is not a .png file\n"));
	return (0);
}
