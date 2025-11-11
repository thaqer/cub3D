/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debuging.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaniatt <tbaniatt@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-01 10:11:05 by tbaniatt          #+#    #+#             */
/*   Updated: 2025-11-01 10:11:05 by tbaniatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_map(t_game *game)
{
	size_t	i;

	if (game && game->map && game->map->map)
	{
		i = 0;
		while (game->map->map[i])
		{
			printf("%s\n", game->map->map[i]);
			i++;
		}
	}
}

void	print_textures_paths(t_game *game)
{
	if (game && game->map)
	{
		printf("North Texture: %s\n", game->map->north);
		printf("South Texture: %s\n", game->map->south);
		printf("West Texture: %s\n", game->map->west);
		printf("East Texture: %s\n", game->map->east);
	}
}

void	print_colors(t_game *game)
{
	if (game && game->map)
	{
		printf("Floor Color: %s\n", game->map->floor);
		printf("Ceiling Color: %s\n", game->map->ceiling);
	}
}

void	print_game_info(t_game *game)
{
	print_textures_paths(game);
	print_colors(game);
	print_map(game);
}


int32_t	test_mlx_functions()
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	mlx_texture_t *tex;

	mlx = mlx_init(800, 600, "MLX42 Example", false);
	if (!mlx)
		return (EXIT_FAILURE);
	tex = mlx_load_png("textures/wall.png");
	if (!tex)
		return (mlx_terminate(mlx), EXIT_FAILURE);

	img = mlx_texture_to_image(mlx, tex);
	mlx_delete_texture(tex);
	if (!img)
		return (mlx_terminate(mlx), EXIT_FAILURE);

	mlx_image_to_window(mlx, img, 0, 0);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
