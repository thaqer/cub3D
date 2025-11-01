/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dqaddomi <dqaddomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:29:04 by tbaniatt          #+#    #+#             */
/*   Updated: 2025/08/28 16:38:25 by dqaddomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc != 2)
		return (ft_putstr_fd("Error: Invalid number of arguments\n", 2), 1);
	if (init_game(argv[1]) == -1)
		return (1);
	return (0);
}
