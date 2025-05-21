/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 04:26:37 by tsomacha          #+#    #+#             */
/*   Updated: 2025/05/21 03:34:07 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/**
 * Main function for the dining philosophers program
 * Checks for correct number of arguments (5 or 6)
 * Validates the input arguments
 * Allocates memory for philosophers and forks
 * Initializes the simulation with ft_start
 * Cleans up resources with ft_exit
 * Displays error messages for invalid input or incorrect argument count
*/
int	main(int argc, char *argv[])
{
	int		size;
	t_philo	*philos;
	t_fork	*forks;
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		if (ft_is_valid(argv, argc))
		{
			size = ft_atol(argv[1]);
			philos = malloc(sizeof(t_philo) * size);
			forks = malloc(sizeof(t_fork) * size);
			if (!philos || !forks)
				return (ft_error("memory allocation fails!"));
			if (ft_start(&table, forks, philos, argv))
				return (ft_error("fail to start the simulation!"));
			if (ft_exit(&table, forks, philos))
				return (ft_error("simulation not exit properly!"));
		}
		else
			ft_error("Invalid arguments!");
	}
	else
		ft_error("Incorrect no of arguments!");
	return (0);
}
