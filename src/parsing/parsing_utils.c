/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dqaddomi <dqaddomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 20:52:00 by dqaddomi          #+#    #+#             */
/*   Updated: 2025/11/24 22:08:46 by dqaddomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	assign_texture(char *line, t_game *game, char *path, char *dir)
{
	if (ft_strncmp(dir, "NO", 2) == 0 && !game->flags->wall_north)
	{
		game->map->north = ft_substr(path, 0, line - path);
		game->flags->wall_north = 1;
		return (0);
	}
	else if (ft_strncmp(dir, "SO", 2) == 0 && !game->flags->wall_south)
	{
		game->map->south = ft_substr(path, 0, line - path);
		game->flags->wall_south = 1;
		return (0);
	}
	else if (ft_strncmp(dir, "WE", 2) == 0 && !game->flags->wall_west)
	{
		game->map->west = ft_substr(path, 0, line - path);
		game->flags->wall_west = 1;
		return (0);
	}
	else if (ft_strncmp(dir, "EA", 2) == 0 && !game->flags->wall_east)
	{
		game->map->east = ft_substr(path, 0, line - path);
		game->flags->wall_east = 1;
		return (0);
	}
	return (-1);
}

int	set_wall_texture(char *line, t_game *game, char *path, char *dir)
{
	if (assign_texture(line, game, path, dir) == -1)
	{
		error_exit(game, "Error: Duplicate or invalid texture\n");
		return (-1);
	}
	return (0);
}

int	parse_wall_texture(char *line, t_game *game)
{
	char	*path;
	char	*dir;

	while (ft_white_space(*line))
		line++;
	dir = line;
	line += 2;
	while (ft_white_space(*line))
		line++;
	path = line;
	while (!ft_white_space(*line) && *line != '\0')
		line++;
	if (set_wall_texture(line, game, path, dir) == -1)
	{
		return (-1);
	}
	return (0);
}

int	parse_color_line(char *line, t_game *game)
{
	while (ft_white_space(*line))
		line++;
	game->type = *line;
	line++;
	while (ft_white_space(*line))
		line++;
	game->color_str = line;
	while (*line && *line != '\n')
		line++;
	if (game->type == 'F' && !game->flags->floor)
	{
		ft_strlcpy(game->map->floor, game->color_str, line - game->color_str + 1);
		game->flags->floor = 1;
	}
	else if (game->type == 'C' && !game->flags->ceiling)
	{
		ft_strlcpy(game->map->ceiling, game->color_str, line - game->color_str + 1);
		game->flags->ceiling = 1;
	}
	else
	{
		error_exit(game, "Error: Duplicate or invalid color\n");
		return (-1);
	}
	return (0);
}

int	all_elements_parsed(t_flags *flags)
{
	if (flags->wall_north && flags->wall_south
		&& flags->wall_west && flags->wall_east
		&& flags->floor && flags->ceiling)
		return (1);
	return (0);
}

int	process_map_line(char *line, t_game *game, int fd)
{
	if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
		|| ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0)
	{
		if (parse_wall_texture(line, game) == -1)
		{
			free(line);
			close(fd);
			return (-1);
		}
	}
	else if (ft_strncmp(line, "F", 1) == 0 || ft_strncmp(line, "C", 1) == 0)
	{
		if (parse_color_line(line, game) == -1)
		{
			free(line);
			close(fd);
			return (-1);
		}
	}
	return (0);
}
