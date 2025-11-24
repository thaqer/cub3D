/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dqaddomi <dqaddomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 16:50:19 by tbaniatt          #+#    #+#             */
/*   Updated: 2025/11/24 14:07:42 by dqaddomi         ###   ########.fr       */
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
	{
		error_init(NULL, "Error: allocate memory for game\n");
		return (NULL);
	}
	game->mlx = NULL;
	game->map = malloc(sizeof(t_map));
	if (!game->map)
	{
		error_init(game, "Error: allocate memory for map\n");
		return (NULL);
	}
	game->flags = malloc(sizeof(t_flags));
	if (!game->flags)
	{
		error_init(game, "Error: allocate memory for flags\n");
		return (NULL);
	}
	game->textures = malloc(sizeof(t_textures));
	if (!game->textures)
	{
		error_init(game, "Error: allocate memory for textures\n");
		return (NULL);
	}
	game->player = malloc(sizeof(t_player));
	if (!game->player)
	{
		error_init(game, "Error: allocate memory for player\n");
		return (NULL);
	}
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
