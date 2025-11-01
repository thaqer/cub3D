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

int	parse_wall_texture(char *line, t_game *game)
{
	char	*path;
	
	while (ft_white_space(*line))
		line++;
	if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
		|| ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0)
	{
		line += 2;
		while (ft_white_space(*line))
			line++;
		path = line;
		while (!ft_white_space(*line) && *line != '\0')
			line++;
		game->map->north = ft_substr(path, 0, line - path);
		game->map->south = ft_substr(path, 0, line - path);
		game->map->west = ft_substr(path, 0, line - path);
		game->map->east = ft_substr(path, 0, line - path);


		// game->textures = malloc(sizeof(t_textures));
		// if (!game->textures)
		// 	return (-1);
		// if (ft_strncmp(path - 2, "NO", 2) == 0)
		// 	game->textures->no = ft_substr(path, 0, line - path);
		// else if (ft_strncmp(path - 2, "SO", 2) == 0)
		// 	game->textures->so = ft_substr(path, 0, line - path);
		// else if (ft_strncmp(path - 2, "WE", 2) == 0)
		// 	game->textures->we = ft_substr(path, 0, line - path);
		// else if (ft_strncmp(path - 2, "EA", 2) == 0)
		// 	game->textures->ea = ft_substr(path, 0, line - path);
	}
	return (0);
}

int	parse_map(char *map_path, t_game *game)
{
	int fd;
	char *line;
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (error_exit(game, "Error: Unable to open map file\n"));
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
			|| ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0)
			parse_wall_texture(line, game);
			////////////////////////////////









		else if (ft_strncmp(line, "F", 1) == 0 || ft_strncmp(line, "C", 1) == 0)
		{
			// Parse floor and ceiling colors
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}