/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaniatt <tbaniatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:05:00 by tbaniatt          #+#    #+#             */
/*   Updated: 2025/11/26 19:01:45 by tbaniatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_ray(t_ray *ray, t_game *game, int x)
{
	ray->camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
	ray->ray_dir_x = game->player->dir_x + game->player->plane_x
		* ray->camera_x;
	ray->ray_dir_y = game->player->dir_y + game->player->plane_y
		* ray->camera_x;
	ray->map_x = (int)game->player->x;
	ray->map_y = (int)game->player->y;
}

void	cast_rays(void *param)
{
	t_game	*game;
	t_ray	ray;
	int		x;

	game = (t_game *)param;
	draw_floor_ceiling(game);
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		init_ray(&ray, game, x);
		if (ray.ray_dir_x == 0)
			ray.delta_dist_x = 1e30;
		else
			ray.delta_dist_x = fabs(1 / ray.ray_dir_x);
		if (ray.ray_dir_y == 0)
			ray.delta_dist_y = 1e30;
		else
			ray.delta_dist_y = fabs(1 / ray.ray_dir_y);
		perform_dda(game, &ray);
		calculate_wall_distance(&ray);
		draw_wall(game, &ray, x);
		x++;
	}
}

// static void	draw_textured_ceiling(t_game *game, int x, int y)
// {
// 	uint32_t	color;
// 	int			tex_x;
// 	int			tex_y;
// 	double		angle;
// 	uint8_t		*texture_bytes;
// 	int			pixel_index;

// 	if (!game->textures->cloud)
// 	{
// 		mlx_put_pixel(game->img, x, y, game->ceiling_color);
// 		return ;
// 	}
// 	texture_bytes = game->textures->cloud->pixels;
// 	angle = atan2(game->player->dir_y, game->player->dir_x);
// 	tex_x = (int)((angle / (2.0 * 3.14159265359) + 0.5)
// 			* game->textures->cloud->width);
// 	tex_x = (tex_x + (x * game->textures->cloud->width) / WINDOW_WIDTH)
// 		% game->textures->cloud->width;
// 	tex_y = (y * game->textures->cloud->height) / (WINDOW_HEIGHT / 2);
// 	if (tex_x < 0)
// 		tex_x = 0;
// 	if (tex_x >= (int)game->textures->cloud->width)
// 		tex_x = game->textures->cloud->width - 1;
// 	if (tex_y < 0)
// 		tex_y = 0;
// 	if (tex_y >= (int)game->textures->cloud->height)
// 		tex_y = game->textures->cloud->height - 1;
// 	pixel_index = (tex_y * game->textures->cloud->width + tex_x) * 4;
// 	color = (texture_bytes[pixel_index] << 24)
// 		| (texture_bytes[pixel_index + 1] << 16)
// 		| (texture_bytes[pixel_index + 2] << 8)
// 		| texture_bytes[pixel_index + 3];
// 	mlx_put_pixel(game->img, x, y, color);
// }

// draw_textured_ceiling(game, x, y);
void	draw_floor_ceiling(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			if (y < WINDOW_HEIGHT / 2)
			{
				mlx_put_pixel(game->img, x, y, game->ceiling_color);
			}
			else
				mlx_put_pixel(game->img, x, y, game->floor_color);
			x++;
		}
		y++;
	}
}

void	calculate_wall_distance(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	ray->line_height = (int)(WINDOW_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WINDOW_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WINDOW_HEIGHT / 2;
	if (ray->draw_end >= WINDOW_HEIGHT)
		ray->draw_end = WINDOW_HEIGHT - 1;
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			ray->wall_dir = 0;
		else
			ray->wall_dir = 1;
	}
	else
	{
		if (ray->step_y > 0)
			ray->wall_dir = 2;
		else
			ray->wall_dir = 3;
	}
}
