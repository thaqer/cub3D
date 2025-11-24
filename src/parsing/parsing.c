/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dqaddomi <dqaddomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 10:32:37 by tbaniatt          #+#    #+#             */
/*   Updated: 2025/11/24 22:08:46 by dqaddomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_white_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	parse_map(char *map_path, t_game *game)
{
	int		fd;
	char	*line;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
	{
		error_exit(game, "Error: Unable to open map file\n");
		return (-1);
	}
	line = get_next_line(fd);
	while (line)
	{
		if (process_map_line(line, game, fd) == -1)
			return (-1);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!all_elements_parsed(game->flags))
	{
		error_exit(game, "Error: Missing map elements\n");
		return (-1);
	}
	return (0);
}
