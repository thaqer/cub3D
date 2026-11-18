/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dqaddomi <dqaddomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 12:38:09 by dqaddomi          #+#    #+#             */
/*   Updated: 2025/12/27 13:26:08 by dqaddomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	extract_digit_info(char *s, int *after_idx, int *sig_digits)
{
	int	i;
	int	start;
	int	end;
	int	j;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && ft_white_space(s[i]))
		i++;
	if (!s[i] || !ft_isdigit(s[i]))
		return (0);
	start = i;
	while (s[i] && ft_isdigit(s[i]))
		i++;
	end = i - 1;
	j = start;
	while (j <= end && s[j] == '0')
		j++;
	if (j > end)
		*sig_digits = 1;
	else
		*sig_digits = end - j + 1;
	*after_idx = i;
	return (1);
}

static int	count_commas(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count);
}

static int	validate_rgb(char *value)
{
	int	num;

	if (!only_digit(value))
		return (-1);
	num = ft_atoi(value);
	if (num < 0 || num > 255)
		return (-1);
	return (num);
}

int	parse_rgb(char *color_str, int *r, int *g, int *b)
{
	char	**rgb;
	int		result;

	if (!color_str || count_commas(color_str) != 2)
		return (-1);
	rgb = ft_split(color_str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		if (rgb)
			ft_free_split(rgb);
		return (-1);
	}
	*r = validate_rgb(rgb[0]);
	*g = validate_rgb(rgb[1]);
	*b = validate_rgb(rgb[2]);
	result = 0;
	if (*r == -1 || *g == -1 || *b == -1)
		result = -1;
	ft_free_split(rgb);
	return (result);
}

int	validate_colors(t_game *game)
{
	int	r;
	int	g;
	int	b;

	if (parse_rgb(game->map->floor, &r, &g, &b) == -1)
	{
		error_exit(NULL, "Error\nInvalid floor color format\n");
		return (-1);
	}
	if (parse_rgb(game->map->ceiling, &r, &g, &b) == -1)
	{
		error_exit(NULL, "Error\nInvalid ceiling color format\n");
		return (-1);
	}
	return (0);
}
