/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaniatt <tbaniatt@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-31 12:25:26 by tbaniatt          #+#    #+#             */
/*   Updated: 2025-10-31 12:25:26 by tbaniatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_game(t_game *game)
{
	size_t	i;

	if (game)
	{
		if (game->map)
		{
			if (game->map->map)
			{
				i = 0;
				while (game->map->map[i])
					free(game->map->map[i++]);
				free(game->map->map);
			}
			free(game->map);
		}
		if (game->flags)
			free(game->flags);
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