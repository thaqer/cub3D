/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dqaddomi <dqaddomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:35:42 by tbaniatt          #+#    #+#             */
/*   Updated: 2025/12/23 21:00:29 by dqaddomi         ###   ########.fr       */
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
	mlx_texture_t	*cloud;
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
	double		tex_pos;
	double		step;
}				t_ray;

typedef struct s_map
{
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	char		*floor;
	char		*ceiling;
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
	double		mouse_x;
	double		mouse_y;
	double		mouse_dx;
	char		*color_str;
	char		type;
	int			result;

}				t_game;

///////debugging functions
void			print_game_info(t_game *game);
void			print_map(t_game *game);
void			print_textures_paths(t_game *game);
void			print_colors(t_game *game);
int32_t			test_mlx_functions(t_game *game); //debugging
//////////////////////////

// initialize.c 
t_game			*init_game(char *map_path);
void			init_player(t_game *game);
uint32_t		rgb_to_uint32(int r, int g, int b);
void			ft_free_split(char **split);

// init_utils.c 
t_game			*malloc_init(t_game *game);
int				parse_color_line(char *line, t_game *game);
void			parse_color(char *color_str, uint32_t *color);
void			init_map_struct(t_map *map);
void			init_flags_struct(t_flags *flags);

// map_parsing.c
int				parse_map_grid(char *map_path, t_game *game);
int				handle_line_error(char *line, int result, int start);

// map_parsing_utils.c
int				valid_map_char(char c);
int				is_line_empty(char *line);
char			*copy_map_line(char *line);
int				open_file_checked(char *path, t_game *game);
void			free_remaining_lines(int fd);

// map_parsing_helper.c
int				handle_count_error(char *line, int result, int start, int fd);
int				set_floor_color(t_game *game, char *line);
int				set_ceiling_color(t_game *game, char *line);
int				count_map_lines(char *map_path, t_game *game);

// line_utils.c
int				is_texture_line(char *line);
int				is_color_line(char *line);
int				count_digits(char *rgb_parts);

// mouse_control.c 
void			handle_mouse_move(double x_pos, double y_pos, void *param);
void			handle_mouse_rotation(t_game *game);
void			init_mouse(t_game *game);

// parsing.c 
int				parse_map(char *map_path, t_game *game);
int				process_map_line(char *line, t_game *game, int fd);
int				all_elements_parsed(t_flags *flags);
int				parse_wall_texture(char *line, t_game *game);
int				ft_white_space(char c);
// end.c 
void			free_game(t_game *game);
int				error_exit(t_game *game, char *message);

// map_validation.c 
int				validate_map(t_game *game);

// map_validation_utils.c
int				check_map_char(t_game *game);
int				players(t_game *game, int *player_x, int *player_y);
int				is_valid_neighbor(char c);

// color_validation.c
int				validate_colors(t_game *game);

// textures_validation.c
int				check_textures(t_game *game);

// run.c 
int				run_game(t_game *game);
void			handle_movement(t_game *game);
void			game_loop(void *param);
void			cast_rays(void *param);
void			draw_floor_ceiling(t_game *game);
void			perform_dda(t_game *game, t_ray *ray);
void			calculate_wall_distance(t_ray *ray);
void			draw_wall(t_game *game, t_ray *ray, int x);
void			handle_sliding_move(t_game *game, double new_x, double new_y);
void			draw_textured_ceiling(t_game *game, int x, int y, double angle);

#endif