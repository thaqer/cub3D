/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniah <daniah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:30:00 by daniah            #+#    #+#             */
/*   Updated: 2025/12/17 16:11:58 by daniah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_texture_line(char *line)
{
	while (ft_white_space(*line))
		line++;
	if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
		|| ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0)
		return (1);
	return (0);
}

int	is_color_line(char *line)
{
	while (ft_white_space(*line))
		line++;
	if (ft_strncmp(line, "F", 1) == 0 || ft_strncmp(line, "C", 1) == 0)
		return (1);
	return (0);
}

int	count_digits(char **rgb_parts)
{
	int	i;
	int	j;

	i = 0;
	while (rgb_parts[i])
	{
		j = 0;
		while (rgb_parts[i][j])
			j++;
		if (j > 3)
			return (-1);
		i++;
	}
	return (0);
}
