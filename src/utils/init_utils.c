/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaniatt <tbaniatt@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:02:09 by tbaniatt          #+#    #+#             */
/*   Updated: 2025/11/14 18:29:09 by tbaniatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

uint32_t	rgb_to_uint32(int r, int g, int b)
{
	return ((r << 24) | (g << 16) | (b << 8) | 255);
}

void	parse_color(char *color_str, uint32_t *color)
{
	char	**rgb_parts;
	int		r, g, b;

	rgb_parts = ft_split(color_str, ',');
	if (!rgb_parts || !rgb_parts[0] || !rgb_parts[1] || !rgb_parts[2])
	{
		*color = 0;
		return;
	}

	r = ft_atoi(rgb_parts[0]);
	g = ft_atoi(rgb_parts[1]);
	b = ft_atoi(rgb_parts[2]);

	// Clamp values to 0-255
	if (r < 0) r = 0;
	if (r > 255) r = 255;
	if (g < 0) g = 0;
	if (g > 255) g = 255;
	if (b < 0) b = 0;
	if (b > 255) b = 255;

	*color = rgb_to_uint32(r, g, b);

	// Free allocated memory
	free(rgb_parts[0]);
	free(rgb_parts[1]);
	free(rgb_parts[2]);
	free(rgb_parts);
}
