/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniah <daniah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:00:00 by daniah            #+#    #+#             */
/*   Updated: 2025/12/17 15:19:23 by daniah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	set_floor_color(t_game *game, char *line)
{
	game->map->floor = ft_substr(game->color_str, 0, line - game->color_str);
	if (!game->map->floor)
		return (error_exit(game, "Error: Memory allocation failed\n"));
	game->flags->floor = 1;
	return (0);
}

int	set_ceiling_color(t_game *game, char *line)
{
	game->map->ceiling = ft_substr(game->color_str, 0,
			line - game->color_str);
	if (!game->map->ceiling)
		return (error_exit(game, "Error: Memory allocation failed\n"));
	game->flags->ceiling = 1;
	return (0);
}

int	handle_count_error(char *line, int result, int start, int fd)
{
	if (handle_line_error(line, result, start) == -1)
	{
		if (line)
			free(line);
		free_remaining_lines(fd);
		ft_putstr_fd("Error: Invalid char in the map\n", 2);
		return (-1);
	}
	return (0);
}

int	count_line(int fd)
{
	char	*line;
	int		start;
	int		i;
	int		result;

	line = get_next_line(fd);
	start = 0;
	i = 0;
	while (line)
	{
		result = is_line_empty(line);
		if (handle_count_error(line, result, start, fd) == -1)
			return (-1);
		if (result > 0)
		{
			start = 1;
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
	return (i);
}

int	count_map_lines(char *map_path, t_game *game)
{
	int	lines;
	int	fd;

	fd = open_file_checked(map_path, game);
	if (fd < 0)
		return (-1);
	lines = count_line(fd);
	close(fd);
	return (lines);
}
