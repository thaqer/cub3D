/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dqaddomi <dqaddomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 20:11:47 by dqaddomi          #+#    #+#             */
/*   Updated: 2025/11/17 21:39:51 by dqaddomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int valid_map_char(char c)
{
    if (c == '0' || c == '1' || c == 'N' || c == 'S'
         || c == 'W' || c == 'E' || c == ' ')
        return (1);
    return (0);
}

static int is_line_empty(char *line)
{
	int		i;
    int     found;
	
	i = 0;
    found = 1;
    if (!line || line[0]  == '\n')
        return (0);
	while(line[i] && line[i] != '\n')
	{
		if (!valid_map_char(line[i]))
			return (0);
        if (line[i] != ' ')
            found = 1;
		i++;
	}
	return (found);
}

static int count_line(int fd)
{
    char     *line;
    int     start;
    int     i;
    
    line = get_next_line(fd);
    start = 0;
    i = 0;
    while (line)
    {
        if (is_line_empty(line))
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

static char *copy_map_line(char *line)
{
    \\Copies a single map line without newline 
    char    *new_line;
    int     len;

    len = 0;
    while (line[len] && line[len] != '\n')
        len++;
    new_line = malloc(sizeof(char) * (len + 1));
    if (!new_line)
        return (NULL);
    ft_strlcpy(new_line, line, len + 1);
    return (new_line);
}

static int process_single_line(t_game *game, char *line, int *i, int *start)
{
    if (is_map_line(line))
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

static int process_map_lines(t_game *game, int fd, char *line, int lines)
{
    int     i;
    int     start;

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

static int read_map(t_game *game, int fd, int lines)
{
    char    *line;

    game->map->map = malloc(sizeof(char *) * (lines + 1));
    if (!game->map->map)
    {
        error_exit(game, "Error: Memory allocation failed\n");
        return (-1);
    }
    line = get_next_line(fd);
    return (process_map_lines(game, fd, line, lines));
}

int parse_map(char *map_path, t_game *game)
{
    int     lines;
    int     fd;

    fd = open(map_path, O_RDONLY);
    if (fd < 0)
    {
        error_exit(game, "Error: Unable to open map file\n");
        return (-1);
    }
    map_lines = count_line();
}
