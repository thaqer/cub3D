/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaniatt <tbaniatt@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-10 16:02:20 by tbaniatt          #+#    #+#             */
/*   Updated: 2025-11-10 16:02:20 by tbaniatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	validate_file_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	if (ft_strncmp(filename + len - 4, ".cub", 4) == 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	game = NULL;
	if (argc != 2)
		return (ft_putstr_fd("Error: Invalid number of arguments\n", 2), 1);
	if (!validate_file_extension(argv[1]))
		return (ft_putstr_fd("Error: File must have .cub extension\n", 2), 1);
	if (init_game(argv[1], game) == -1)
		return (1);
	// init_window(game);
	
	return (0);
}
