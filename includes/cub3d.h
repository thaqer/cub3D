/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaniatt <tbaniatt@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:35:42 by tbaniatt          #+#    #+#             */
/*   Updated: 2025/11/15 13:45:47 by tbaniatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <math.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080

typedef struct s_flags
{
	int			wall_north;
	int			wall_south;
	int			wall_west;
	int			wall_east;
	int			floor;
	int			ceiling;
	int			map;

}				t_flags;

typedef struct s_textures
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
}				t_textures;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;

typedef struct s_ray
{
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		side_dist_x;
	double		side_dist_y;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	double		perp_wall_dist;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			wall_dir;
}				t_ray;

typedef struct s_map
{
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	char		floor[12];
	char		ceiling[12];
	char		**map;

}				t_map;

typedef struct s_game
{
	mlx_t		*mlx;
	t_map		*map;
	t_flags		*flags;
	t_textures	*textures;
	t_player	*player;
	mlx_image_t	*img;
	uint32_t	floor_color;
	uint32_t	ceiling_color;

}				t_game;

///////debugging functions
void			print_game_info(t_game *game);
void			print_map(t_game *game);
void			print_textures_paths(t_game *game);
void			print_colors(t_game *game);
int32_t			test_mlx_functions(t_game *game);
//////////////////////////

t_game			*init_game(char *map_path);
t_game			*malloc_init(t_game *game);
void			init_player(t_game *game);
int				parse_map(char *map_path, t_game *game);
void			free_game(t_game *game);
int				error_exit(t_game *game, char *message);
int				run_game(t_game *game);
void			handle_movement(t_game *game);
void			game_loop(void *param);
uint32_t		rgb_to_uint32(int r, int g, int b);
void			parse_color(char *color_str, uint32_t *color);
void			cast_rays(void *param);
void			draw_floor_ceiling(t_game *game);
void			perform_dda(t_game *game, t_ray *ray);
void			calculate_wall_distance(t_ray *ray);
void			draw_wall(t_game *game, t_ray *ray, int x);

#endif
