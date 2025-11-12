/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaniatt <tbaniatt@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-30 17:35:42 by tbaniatt          #+#    #+#             */
/*   Updated: 2025-10-30 17:35:42 by tbaniatt         ###   ########.fr       */
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

typedef struct s_images
{
	mlx_image_t		*north;
	mlx_image_t		*south;
	mlx_image_t		*west;
	mlx_image_t		*east;
}				t_images;

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
	t_images	*images;

}				t_game;

///////debugging functions
void			print_game_info(t_game *game);
void			print_map(t_game *game);
void			print_textures_paths(t_game *game);
void			print_colors(t_game *game);
int32_t			test_mlx_functions(t_game *game);
//////////////////////////

t_game			*init_game(char *map_path);
int				parse_map(char *map_path, t_game *game);
void			free_game(t_game *game);
int				error_exit(t_game *game, char *message);
int				run_game(t_game *game);
void			key_hook(mlx_key_data_t keydata, void *param);

#endif
