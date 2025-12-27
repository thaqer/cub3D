/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dqaddomi <dqaddomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:30:00 by daniah            #+#    #+#             */
/*   Updated: 2025/12/27 13:24:46 by dqaddomi         ###   ########.fr       */
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

int	count_digits(char *rgb_parts)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (rgb_parts[i])
	{
		if (ft_isdigit(rgb_parts[i]))
			count++;
		i++;
	}
	if (count > 3)
		return (-1);
	return (0);
}

int	only_digit(char *str)
{
	int	i;
	int	sig;

	if (!str)
		return (0);
	if (!extract_digit_info(str, &i, &sig))
		return (0);
	if (sig > 3)
		return (0);
	while (str[i])
	{
		if (!ft_white_space(str[i]))
			return (0);
		i++;
	}
	return (1);
}
