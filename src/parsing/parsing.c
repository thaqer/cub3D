/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dqaddomi <dqaddomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 10:32:37 by tbaniatt          #+#    #+#             */
/*   Updated: 2025/11/25 18:42:53 by dqaddomi         ###   ########.fr       */
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
		{
			while (line)
			{
				line = get_next_line(fd);
				free(line);
			}
			return (-1);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!all_elements_parsed(game->flags))
	{
		error_exit(NULL, "Error: Missing map elements\n");
		return (-1);
	}
	return (0);
}
