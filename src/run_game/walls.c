/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaniatt <tbaniatt@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-26 16:00:08 by tbaniatt          #+#    #+#             */
/*   Updated: 2025/11/26 19:06:13 by tbaniatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static mlx_texture_t	*get_wall_texture(t_game *game, t_ray *ray)
{
	if (ray->wall_dir == 0)
		return (game->textures->east);
	else if (ray->wall_dir == 1)
		return (game->textures->west);
	else if (ray->wall_dir == 2)
		return (game->textures->south);
	else
		return (game->textures->north);
}

//cal to fix mirror effect
static int	calculate_tex_x(t_ray *ray, t_game *game, mlx_texture_t *texture)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = game->player->y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = game->player->x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)texture->width);
	if ((ray->side == 0 && ray->ray_dir_x < 0) || (ray->side == 1
			&& ray->ray_dir_y > 0))
		tex_x = texture->width - tex_x - 1;
	return (tex_x);
}

static void	render_wall_column(t_game *game, t_ray *ray, int x, int tex_x)
{
	mlx_texture_t	*texture;
	uint8_t			*pixel;
	int				y;
	int				tex_y;
	uint32_t		color;

	texture = get_wall_texture(game, ray);
	ray->step = 1.0 * texture->height / ray->line_height;
	ray->tex_pos = (ray->draw_start - WINDOW_HEIGHT / 2 + ray->line_height / 2)
		* ray->step;
	y = ray->draw_start - 1;
	while (++y <= ray->draw_end)
	{
		tex_y = (int)ray->tex_pos % texture->height;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= (int)texture->height)
			tex_y = texture->height - 1;
		ray->tex_pos += ray->step;
		pixel = &texture->pixels[(tex_y * texture->width + tex_x) * 4];
		color = (pixel[0] << 24) | (pixel[1] << 16)
			| (pixel[2] << 8) | pixel[3];
		mlx_put_pixel(game->img, x, y, color);
	}
}

void	draw_wall(t_game *game, t_ray *ray, int x)
{
	mlx_texture_t	*texture;
	int				tex_x;

	texture = get_wall_texture(game, ray);
	tex_x = calculate_tex_x(ray, game, texture);
	render_wall_column(game, ray, x, tex_x);
}
