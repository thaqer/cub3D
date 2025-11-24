/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dqaddomi <dqaddomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 12:38:09 by dqaddomi          #+#    #+#             */
/*   Updated: 2025/11/24 20:05:34 by dqaddomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	only_digit(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
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

// Validates and converts RGB string value to integer (0-255)
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

// Parses RGB color string into individual R, G, B values 
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

// Validates floor and ceiling colors
int	validate_colors(t_game *game)
{
	int	r;
	int	g;
	int	b;

	if (parse_rgb(game->map->floor, &r, &g, &b) == -1)
    {
        error_exit(game, "Error: Invalid floor color format\n");
		return (-1);
    }
	if (parse_rgb(game->map->ceiling, &r, &g, &b) == -1)
    {
        error_exit(game, "Error: Invalid ceiling color format\n");
		return (-1);
    }
	return (0);
}
