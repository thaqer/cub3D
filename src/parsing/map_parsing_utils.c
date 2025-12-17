/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniah <daniah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:50:00 by dqaddomi          #+#    #+#             */
/*   Updated: 2025/12/17 14:58:57 by daniah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	valid_map_char(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'W' || c == 'E'
		|| c == ' ')
		return (1);
	return (0);
}

int	is_line_empty(char *line)
{
	int	i;
	int	found;

	i = 0;
	found = 1;
	if (!line || line[0] == '\n')
		return (0);
	while (line[i] && line[i] != '\n')
	{
		if (!valid_map_char(line[i]))
			return (-1);
		if (line[i] != ' ')
			found = 1;
		i++;
	}
	return (found);
}

int	open_file_checked(char *path, t_game *game)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		error_exit(game, "Error: Unable to open map file\n");
		return (-1);
	}
	return (fd);
}

void	free_remaining_lines(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}

int	handle_line_error(char *line, int result, int start)
{
	if (result == -1 && start)
	{
		ft_putstr_fd("Error: Invalid char in the map\n", 2);
		return (-1);
	}
	if (start && line[0] != '\n' && result <= 0)
	{
		free(line);
		return (-1);
	}
	return (0);
}
