/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debuging.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaniatt <tbaniatt@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-01 10:11:05 by tbaniatt          #+#    #+#             */
/*   Updated: 2025-11-01 10:11:05 by tbaniatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	print_map(t_game *game)
{
	size_t	i;

	if (game && game->map && game->map->map)
	{
		i = 0;
		while (game->map->map[i])
		{
			printf("%s\n", game->map->map[i]);
			i++;
		}
	}
}