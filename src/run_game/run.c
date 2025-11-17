/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dqaddomi <dqaddomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 18:13:45 by tbaniatt          #+#    #+#             */
/*   Updated: 2025/11/17 20:28:15 by dqaddomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int run_game(t_game *game)
{
	game->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D", false);
	if (!game->mlx)
		return (error_exit(game, "Error: Failed to initialize MLX\n"));
	game->img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->img)
		return (error_exit(game, "Error: Failed to create image\n"));
	game->textures->north = mlx_load_png(game->map->north);
	if (!game->textures->north)
		return (error_exit(game, "Error: Failed to load north texture\n"));
	game->textures->south = mlx_load_png(game->map->south);
	if (!game->textures->south)
		return (error_exit(game, "Error: Failed to load south texture\n"));
	game->textures->west = mlx_load_png(game->map->west);
	if (!game->textures->west)
		return (error_exit(game, "Error: Failed to load west texture\n"));
	game->textures->east = mlx_load_png(game->map->east);
	if (!game->textures->east)
		return (error_exit(game, "Error: Failed to load east texture\n"));
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	init_mouse(game);
	mlx_loop_hook(game->mlx, &game_loop, game);
	mlx_loop(game->mlx);
	free_game(game);
	return (EXIT_SUCCESS);
}


void	handle_movement(t_game *game)
{
	double	move_speed = 0.05;
	double	rot_speed = 0.05;
	double	old_dir_x;
	double	old_plane_x;

	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT_SHIFT) || 
		mlx_is_key_down(game->mlx, MLX_KEY_RIGHT_SHIFT))
		move_speed *= 2;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		if (game->map->map[(int)(game->player->y)][(int)(game->player->x + game->player->dir_x * move_speed)] != '1')// i need to make it check all dir F B L and R 
			game->player->x += game->player->dir_x * move_speed;
		if (game->map->map[(int)(game->player->y + game->player->dir_y * move_speed)][(int)(game->player->x)] != '1')
			game->player->y += game->player->dir_y * move_speed;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		if (game->map->map[(int)(game->player->y)][(int)(game->player->x - game->player->dir_x * move_speed)] != '1')
			game->player->x -= game->player->dir_x * move_speed;
		if (game->map->map[(int)(game->player->y - game->player->dir_y * move_speed)][(int)(game->player->x)] != '1')
			game->player->y -= game->player->dir_y * move_speed;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		if (game->map->map[(int)(game->player->y)][(int)(game->player->x - game->player->dir_y * move_speed)] != '1')
			game->player->x -= game->player->dir_y * move_speed;
		if (game->map->map[(int)(game->player->y + game->player->dir_x * move_speed)][(int)(game->player->x)] != '1')
			game->player->y += game->player->dir_x * move_speed;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		if (game->map->map[(int)(game->player->y)][(int)(game->player->x + game->player->dir_y * move_speed)] != '1')
			game->player->x += game->player->dir_y * move_speed;
		if (game->map->map[(int)(game->player->y - game->player->dir_x * move_speed)][(int)(game->player->x)] != '1')
			game->player->y -= game->player->dir_x * move_speed;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		old_dir_x = game->player->dir_x;
		game->player->dir_x = game->player->dir_x * cos(rot_speed) - game->player->dir_y * sin(rot_speed);
		game->player->dir_y = old_dir_x * sin(rot_speed) + game->player->dir_y * cos(rot_speed);
		old_plane_x = game->player->plane_x;
		game->player->plane_x = game->player->plane_x * cos(rot_speed) - game->player->plane_y * sin(rot_speed);
		game->player->plane_y = old_plane_x * sin(rot_speed) + game->player->plane_y * cos(rot_speed);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		old_dir_x = game->player->dir_x;
		game->player->dir_x = game->player->dir_x * cos(-rot_speed) - game->player->dir_y * sin(-rot_speed);
		game->player->dir_y = old_dir_x * sin(-rot_speed) + game->player->dir_y * cos(-rot_speed);
		old_plane_x = game->player->plane_x;
		game->player->plane_x = game->player->plane_x * cos(-rot_speed) - game->player->plane_y * sin(-rot_speed);
		game->player->plane_y = old_plane_x * sin(-rot_speed) + game->player->plane_y * cos(-rot_speed);
	}
}

void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	handle_movement(game);
	cast_rays(param);
}

static void	init_ray(t_ray *ray, t_game *game, int x)
{
	ray->camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
	ray->ray_dir_x = game->player->dir_x + game->player->plane_x * ray->camera_x;
	ray->ray_dir_y = game->player->dir_y + game->player->plane_y * ray->camera_x;
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

void	draw_floor_ceiling(t_game *game)
{
	int	x, y;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			if (y < WINDOW_HEIGHT / 2)
				mlx_put_pixel(game->img, x, y, game->ceiling_color);
			else
				mlx_put_pixel(game->img, x, y, game->floor_color);
			x++;
		}
		y++;
	}
}

void	perform_dda(t_game *game, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player->x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player->x) * ray->delta_dist_x;
	}

	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player->y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player->y) * ray->delta_dist_y;
	}
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}

		// Check bounds before accessing the map
		if (ray->map_x < 0 || ray->map_y < 0 || !game->map->map[ray->map_y])
		{
			ray->hit = 1;
			break;
		}
		if (game->map->map[ray->map_y][ray->map_x] == '\0')
		{
			ray->hit = 1;  // Treat end of row as a wall hit
			break;
		}
		if (game->map->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
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
			ray->wall_dir = 0; // East
		else
			ray->wall_dir = 1; // West
	}
	else
	{
		if (ray->step_y > 0)
			ray->wall_dir = 2; // South
		else
			ray->wall_dir = 3; // North
	}
}

void	draw_wall(t_game *game, t_ray *ray, int x)
{
	mlx_texture_t	*texture;
	uint32_t		*texture_data;
	uint32_t		color;
	int				y;
	int				tex_x;
	int				tex_y;
	double			wall_x;
	double			step;
	double			tex_pos;

	if (ray->wall_dir == 0)
		texture = game->textures->east;
	else if (ray->wall_dir == 1)
		texture = game->textures->west;
	else if (ray->wall_dir == 2)
		texture = game->textures->south;
	else
		texture = game->textures->north;

	if (ray->side == 0)
		wall_x = game->player->y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = game->player->x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);

	tex_x = (int)(wall_x * (double)texture->width);
	if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1 && ray->ray_dir_y < 0))
		tex_x = texture->width - tex_x - 1;

	step = 1.0 * texture->height / ray->line_height;
	tex_pos = (ray->draw_start - WINDOW_HEIGHT / 2 + ray->line_height / 2) * step;
	texture_data = (uint32_t *)texture->pixels;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = (int)tex_pos % texture->height;
		if (tex_y < 0) tex_y = 0;
		if (tex_y >= (int)texture->height) tex_y = texture->height - 1;
		tex_pos += step;
		color = texture_data[tex_y * texture->width + tex_x];
		if (ray->side == 0)
			color = (color >> 1) & 8355711;
		mlx_put_pixel(game->img, x, y, color);
		y++;
	}
}
