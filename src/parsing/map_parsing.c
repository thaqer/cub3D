/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dqaddomi <dqaddomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 20:11:47 by dqaddomi          #+#    #+#             */
/*   Updated: 2025/11/24 10:54:55 by dqaddomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	count_line(int fd, t_game *game)
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
		if (result == -1 && start)
		{
			free(line);
			error_exit(game, "Error: Invalid char in the map\n");
			return (-1);
		}
		if (result > 0)
		{
			start = 1;
			i++;
		}
		else if (start && line[0] != '\n')
		{
			free(line);
			return (-1);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (i);
}

static int	process_single_line(t_game *game, char *line, int *i, int *start)
{
	int	result;

	result = is_line_empty(line);
	if (result == -1 && *start)
	{
		free(line);
		error_exit(game, "Error: Invalid char in the map\n");
		return (-1);
	}
	if (result > 0)
	{
		*start = 1;
		game->map->map[(*i)++] = copy_map_line(line);
		if (!game->map->map[*i - 1])
		{
			free(line);
			error_exit(game, "Error: Memory allocation failed\n");
			return (-1);
		}
	}
	else if (*start && line[0] != '\n')
	{
		free(line);
		error_exit(game, "Error: Invalid map format\n");
		return (-1);
	}
	return (0);
}

static int	process_map_lines(t_game *game, int fd, char *line, int lines)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (line && i < lines)
	{
		if (process_single_line(game, line, &i, &start) == -1)
			return (-1);
		free(line);
		line = get_next_line(fd);
	}
	game->map->map[i] = NULL;
	return (0);
}

static int	read_map(t_game *game, int fd, int lines)
{
	char	*line;

	game->map->map = malloc(sizeof(char *) * (lines + 1));
	if (!game->map->map)
	{
		error_exit(game, "Error: Memory allocation failed\n");
		return (-1);
	}
	line = get_next_line(fd);
	return (process_map_lines(game, fd, line, lines));
}

int	parse_map_grid(char *map_path, t_game *game)
{
	int	lines;
	int	fd;

	fd = open_file_checked(map_path, game);
	if (fd < 0)
		return (-1);
	lines = count_line(fd, game);
	close(fd);
	if (lines <= 0)
	{
		//error_exit(game, "Error: Invalid or empty map\n"); //double free
		return (-1);
	}
	fd = open_file_checked(map_path, game);
	if (fd < 0)
		return (-1);
	if (read_map(game, fd, lines) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	game->flags->map = 1;
	return (0);
}
