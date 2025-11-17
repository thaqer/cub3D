/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dqaddomi <dqaddomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 20:11:47 by dqaddomi          #+#    #+#             */
/*   Updated: 2025/11/11 20:18:08 by dqaddomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int valid_map_char(char c)
{
    return (c == '0' || c == '1' || c == 'N' || c == 'S'
         || c == 'W' || c == 'E' || c == ' ');
}
static int is_line_empty(char *line)
{
	int		i;
	
	i = 0;
    if (!line || line[0]  == '\n')
        return (0);
	while(line[i] && line[i] != '\n')
	{
		if (!ft_white_space(line[i]))
			return (0);
		i++;
	}
	return (1);
}

static int valid_line()
{
    int     *line;
    int     start;
    int     
}
