/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dqaddomi <dqaddomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:02:09 by tbaniatt          #+#    #+#             */
/*   Updated: 2025/11/25 19:43:27 by dqaddomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

uint32_t	rgb_to_uint32(int r, int g, int b)
{
	return ((r << 24) | (g << 16) | (b << 8) | 255);
}

static int	clamp_color_value(int value)
{
	if (value < 0)
		return (0);
	if (value > 255)
		return (255);
	return (value);
}

static void	extract_rgb_values(char **rgb_parts, int *r, int *g, int *b)
{
	*r = ft_atoi(rgb_parts[0]);
	*g = ft_atoi(rgb_parts[1]);
	*b = ft_atoi(rgb_parts[2]);
	*r = clamp_color_value(*r);
	*g = clamp_color_value(*g);
	*b = clamp_color_value(*b);
}

void	parse_color(char *color_str, uint32_t *color)
{
	char	**rgb_parts;
	int		r;
	int		g;
	int		b;

	rgb_parts = ft_split(color_str, ',');
	if (!rgb_parts || !rgb_parts[0] || !rgb_parts[1] || !rgb_parts[2])
	{
		*color = 0;
		ft_free_split(rgb_parts);
		return ;
	}
	extract_rgb_values(rgb_parts, &r, &g, &b);
	*color = rgb_to_uint32(r, g, b);
	free(rgb_parts[0]);
	free(rgb_parts[1]);
	free(rgb_parts[2]);
	free(rgb_parts);
}
