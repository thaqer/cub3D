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

#ifndef CUBE3D_H
# define CUBE3D_H

# include <mlx.h>
# include "../libft/libft.h"
# include "get_next_line.h"
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>

typedef struct s_flags
{
	int	wall_north;
	int	wall_south;
	int	wall_west;
	int	wall_east;
	int	floor;
	int	ceiling;
	int	map;

}	t_flags;

typedef struct s_textures
{
	void	*no;
	void	*so;
	void	*we;
	void	*ea;
}	t_textures;

typedef struct s_map
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	floor[12];
	char	ceiling[12];
	char	**map;

} t_map;
 
typedef struct s_game
{
	void	*mlx;
	void	*window;
	
	t_map	*map;
	t_flags	*flags;
	t_textures	*textures;
	
}	t_game;


int		init_game(char *map_path);
int		parse_map(char *map_path, t_game *game);
void	free_game(t_game *game);
int		error_exit(t_game *game, char *message);

#endif
