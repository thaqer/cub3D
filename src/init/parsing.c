// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   parsing.c                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: daniah <daniah@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/10/31 10:32:37 by tbaniatt          #+#    #+#             */
// /*   Updated: 2025/11/16 23:31:43 by daniah           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../includes/cub3d.h"

// int	ft_white_space(char c)
// {
// 	if (c == ' ' || c == '\t' || c == '\n'
// 		|| c == '\v' || c == '\f' || c == '\r')
// 		return (1);
// 	return (0);
// }

// static void	parse_utils(char **direction, char *line, char *path, int *flag)
// {
// 	*direction = ft_substr(path, 0, line - path);
// 	if (*flag == 0)
// 		*flag = 1;
// }

// static int	parse_wall_texture(char *line, t_game *game)
// {
// 	char	*path;
// 	char	*direction;

// 	while (ft_white_space(*line))
// 		line++;
// 	direction = line;
// 	line += 2;
// 	while (ft_white_space(*line))
// 		line++;
// 	path = line;
// 	while (!ft_white_space(*line) && *line != '\0')
// 		line++;
// 	if (ft_strncmp(direction, "NO", 2) == 0 && !game->flags->wall_north)
// 		parse_utils(&game->map->north, line, path, &game->flags->wall_north);
// 	else if (ft_strncmp(direction, "SO", 2) == 0 && !game->flags->wall_south)
// 		parse_utils(&game->map->south, line, path, &game->flags->wall_south);
// 	else if (ft_strncmp(direction, "WE", 2) == 0 && !game->flags->wall_west)
// 		parse_utils(&game->map->west, line, path, &game->flags->wall_west);
// 	else if (ft_strncmp(direction, "EA", 2) == 0 && !game->flags->wall_east)
// 		parse_utils(&game->map->east, line, path, &game->flags->wall_east);
// 	else
// 		return (-1);
// 	return (0);
// }

// static	int	parse_color_utils(t_game *game, char type,
// 								char *color_str, char *line)
// {
// 	if (type == 'F' && !game->flags->floor)
// 	{
// 		ft_strlcpy(game->map->floor, color_str, line - color_str + 1);
// 		parse_color(game->map->floor, &game->floor_color);
// 		game->flags->floor = 1;
// 	}
// 	else if (type == 'C' && !game->flags->ceiling)
// 	{
// 		ft_strlcpy(game->map->ceiling, color_str, line - color_str + 1);
// 		parse_color(game->map->ceiling, &game->ceiling_color);
// 		game->flags->ceiling = 1;
// 	}
// 	else
// 		return (-1);
// 	return (0);
// }

// static int	parse_color_values(char *line, t_game *game)
// {
// 	char	*color_str;
// 	char	type;

// 	while (ft_white_space(*line))
// 		line++;
// 	type = *line;
// 	line++;
// 	while (ft_white_space(*line))
// 		line++;
// 	color_str = line;
// 	while (*line && *line != '\n')
// 		line++;
// 	if (parse_color_utils(game, type, color_str, line) == -1)
// 		return (-1);
// 	return (0);
// }

// static int	all_elements_parsed(t_flags *flags)
// {
// 	if (flags->wall_north && flags->wall_south
// 		&& flags->wall_west && flags->wall_east
// 		&& flags->floor && flags->ceiling)
// 		return (1);
// 	return (0);
// }

// int	parse_map(char *map_path, t_game *game)
// {
// 	int		fd;
// 	char	*line;
// 	char	**temp_map;
// 	int		map_line_count;

// 	temp_map = NULL;
// 	map_line_count = 0;
// 	fd = open(map_path, O_RDONLY);
// 	if (fd < 0)
// 		return (-1);
// 	line = get_next_line(fd);
// 	while (line && !all_elements_parsed(game->flags))
// 	{
// 		if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
// 			|| ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0)
// 		{
// 			if (parse_wall_texture(line, game) == -1)
// 				return (free(line), close(fd), -1);
// 		}
// 		else if (ft_strncmp(line, "F", 1) == 0 || ft_strncmp(line, "C", 1) == 0)
// 		{
// 			if (parse_color_values(line, game) == -1)
// 				return (free(line), close(fd), -1);
// 		}
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	if (!all_elements_parsed(game->flags))
// 		return (close(fd), -1);
// 	while (line)
// 	{
// 		if (ft_strlen(line) > 1)
// 		{
// 			temp_map = realloc(temp_map, sizeof(char *) * (map_line_count + 2));
// 			if (!temp_map)
// 				return (free(line), close(fd), -1);
// 			if (line[ft_strlen(line) - 1] == '\n')
// 				line[ft_strlen(line) - 1] = '\0';
// 			temp_map[map_line_count] = ft_strdup(line);
// 			map_line_count++;
// 			temp_map[map_line_count] = NULL;
// 		}
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// 	game->map->map = temp_map;
// 	return (0);
// }
