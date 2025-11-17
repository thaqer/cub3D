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

	if (argc != 2)
		return (error_exit(NULL, "Error: Invalid number of arguments\n"));
	if (!validate_file_extension(argv[1]))
		return (error_exit(NULL, "Error: File must have .cub extension\n"));
	game = init_game(argv[1]);
	if (!game)
		return (1);
	if (run_game(game) == -1)
		return (1);	
	return (0);
}
