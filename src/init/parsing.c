/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaniatt <tbaniatt@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-31 10:32:37 by tbaniatt          #+#    #+#             */
/*   Updated: 2025-10-31 10:32:37 by tbaniatt         ###   ########.fr       */
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

static int	parse_wall_texture(char *line, t_game *game)
{
	char	*path;
	char	*direction;

	while (ft_white_space(*line))
		line++;
	direction = line;
	line += 2;
	while (ft_white_space(*line))
		line++;
	path = line;
	while (!ft_white_space(*line) && *line != '\0')
		line++;
	if (ft_strncmp(direction, "NO", 2) == 0 && !game->flags->wall_north)
	{
		game->map->north = ft_substr(path, 0, line - path);
		game->flags->wall_north = 1;
	}
	else if (ft_strncmp(direction, "SO", 2) == 0 && !game->flags->wall_south)
	{
		game->map->south = ft_substr(path, 0, line - path);
		game->flags->wall_south = 1;
	}
	else if (ft_strncmp(direction, "WE", 2) == 0 && !game->flags->wall_west)
	{
		game->map->west = ft_substr(path, 0, line - path);
		game->flags->wall_west = 1;
	}
	else if (ft_strncmp(direction, "EA", 2) == 0 && !game->flags->wall_east)
	{
		game->map->east = ft_substr(path, 0, line - path);
		game->flags->wall_east = 1;
	}
	else
		return (error_exit(game, "Error: Duplicate or invalid texture\n"));
	return (0);
}

static int	parse_color(char *line, t_game *game)
{
	char	*color_str;
	char	type;

	while (ft_white_space(*line))
		line++;
	type = *line;
	line++;
	while (ft_white_space(*line))
		line++;
	color_str = line;
	while (*line && *line != '\n')
		line++;
	if (type == 'F' && !game->flags->floor)
	{
		ft_strlcpy(game->map->floor, color_str, line - color_str + 1);
		game->flags->floor = 1;
	}
	else if (type == 'C' && !game->flags->ceiling)
	{
		ft_strlcpy(game->map->ceiling, color_str, line - color_str + 1);
		game->flags->ceiling = 1;
	}
	else
		return (error_exit(game, "Error: Duplicate or invalid color\n"));
	return (0);
}

static int	all_elements_parsed(t_flags *flags)
{
	if (flags->wall_north && flags->wall_south
		&& flags->wall_west && flags->wall_east
		&& flags->floor && flags->ceiling)
		return (1);
	return (0);
}

int	parse_map(char *map_path, t_game *game)
{
	int		fd;
	char	*line;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (error_exit(game, "Error: Unable to open map file\n"));
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
			|| ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0)
		{
			if (parse_wall_texture(line, game) == -1)
				return (free(line), close(fd), -1);
		}
		else if (ft_strncmp(line, "F", 1) == 0 || ft_strncmp(line, "C", 1) == 0)
		{
			if (parse_color(line, game) == -1)
				return (free(line), close(fd), -1);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!all_elements_parsed(game->flags))
		return (error_exit(game, "Error: Missing map elements\n"));
	return (0);
}
