/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dqaddomi <dqaddomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:30:00 by daniah            #+#    #+#             */
/*   Updated: 2025/12/22 21:20:19 by dqaddomi         ###   ########.fr       */
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
	int	count;

	i = 0;
	while (rgb_parts[i])
	{
		j = 0;
		count = 0;
		while (rgb_parts[i][j])
		{
			if (ft_isdigit(rgb_parts[i][j]))
				count++;
			j++;
		}
		if (count > 3)
			return (-1);
		i++;
	}
	return (0);
}
