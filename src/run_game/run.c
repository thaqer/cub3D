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

int	run_game(t_game *game)
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

static int	check_corner(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_y < 0)
		return (0);
	if (!game->map->map[map_y] || !game->map->map[map_y][map_x])
		return (0);
	if (game->map->map[map_y][map_x] == '1')
		return (0);
	return (1);
}

/* we check all four corners of the player rectangle
to avoid going through walls*/
/* margin is a small value 
***to ensure we are slightly inside the walkable area*/
/*if we want to make it possible to walk through narrow spaces
***we need to make margin small as possible*/
static int	check_valid_move(t_game *game, double new_x, double new_y)
{
	double	margin;
	int		i;
	double	corners_x[4];
	double	corners_y[4];

	margin = 0.005;
	corners_x[0] = new_x + margin;
	corners_y[0] = new_y + margin;
	corners_x[1] = new_x - margin;
	corners_y[1] = new_y + margin;
	corners_x[2] = new_x + margin;
	corners_y[2] = new_y - margin;
	corners_x[3] = new_x - margin;
	corners_y[3] = new_y - margin;
	i = 0;
	while (i < 4)
	{
		if (!check_corner(game, corners_x[i], corners_y[i]))
			return (0);
		i++;
	}
	return (1);
}

/* This function handles collision detection with wall sliding
** If diagonal movement is blocked, it tries moving along each axis separately
** This allows the player to "slide" along walls instead of getting stuck */
static void	handle_sliding_move(t_game *game, double new_x, double new_y)
{
	double	current_x;
	double	current_y;

	current_x = game->player->x;
	current_y = game->player->y;
	if (check_valid_move(game, new_x, new_y))
	{
		game->player->x = new_x;
		game->player->y = new_y;
		return ;
	}
	if (check_valid_move(game, new_x, current_y))
	{
		game->player->x = new_x;
		return ;
	}
	if (check_valid_move(game, current_x, new_y))
	{
		game->player->y = new_y;
		return ;
	}
}

static void	handle_player_movement(t_game *game)
{
	double	move_speed;
	double	new_x;
	double	new_y;

	move_speed = 0.05;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT_SHIFT)
		|| mlx_is_key_down(game->mlx, MLX_KEY_RIGHT_SHIFT))
		move_speed *= 2;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		new_x = game->player->x + game->player->dir_x * move_speed;
		new_y = game->player->y + game->player->dir_y * move_speed;
		handle_sliding_move(game, new_x, new_y);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		new_x = game->player->x - game->player->dir_x * move_speed;
		new_y = game->player->y - game->player->dir_y * move_speed;
		handle_sliding_move(game, new_x, new_y);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		new_x = game->player->x - game->player->dir_y * move_speed;
		new_y = game->player->y + game->player->dir_x * move_speed;
		handle_sliding_move(game, new_x, new_y);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		new_x = game->player->x + game->player->dir_y * move_speed;
		new_y = game->player->y - game->player->dir_x * move_speed;
		handle_sliding_move(game, new_x, new_y);
	}
}

static void	rotate_player(t_game *game, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player->dir_x;
	game->player->dir_x = game->player->dir_x * cos(rot_speed)
		- game->player->dir_y * sin(rot_speed);
	game->player->dir_y = old_dir_x * sin(rot_speed)
		+ game->player->dir_y * cos(rot_speed);
	old_plane_x = game->player->plane_x;
	game->player->plane_x = game->player->plane_x * cos(rot_speed)
		- game->player->plane_y * sin(rot_speed);
	game->player->plane_y = old_plane_x * sin(rot_speed)
		+ game->player->plane_y * cos(rot_speed);
}

void	handle_movement(t_game *game)
{
	double	rot_speed;

	handle_player_movement(game);
	rot_speed = 0.03;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_player(game, rot_speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_player(game, -rot_speed);
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
	ray->ray_dir_x = game->player->dir_x
		+ game->player->plane_x * ray->camera_x;
	ray->ray_dir_y = game->player->dir_y
		+ game->player->plane_y * ray->camera_x;
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
	int	x;
	int	y;

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
		ray->side_dist_x = (ray->map_x + 1.0 - game->player->x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player->y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player->y)
			* ray->delta_dist_y;
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
		if (ray->map_x < 0 || ray->map_y < 0 || !game->map->map[ray->map_y])
		{
			ray->hit = 1;
			break ;
		}
		if (game->map->map[ray->map_y][ray->map_x] == '\0')
		{
			ray->hit = 1;
			break ;
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
	if ((ray->side == 0 && ray->ray_dir_x > 0)
		|| (ray->side == 1 && ray->ray_dir_y < 0))
		tex_x = texture->width - tex_x - 1;
	return (tex_x);
}

static void	render_wall_column(t_game *game, t_ray *ray, int x, int tex_x)
{
	mlx_texture_t	*texture;
	uint32_t		*texture_data;
	int				y;
	int				tex_y;
	uint32_t		color;

	texture = get_wall_texture(game, ray);
	ray->step = 1.0 * texture->height / ray->line_height;
	ray->tex_pos = (ray->draw_start - WINDOW_HEIGHT / 2 + ray->line_height / 2)
		* ray->step;
	texture_data = (uint32_t *)texture->pixels;
	y = ray->draw_start - 1;
	while (++y <= ray->draw_end)
	{
		tex_y = (int)ray->tex_pos % texture->height;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= (int)texture->height)
			tex_y = texture->height - 1;
		ray->tex_pos += ray->step;
		color = texture_data[tex_y * texture->width + tex_x];
		// if (ray->side == 0)
		// 	color = (color >> 1) & 8355711;
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
