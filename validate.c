/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 04:04:21 by tsomacha          #+#    #+#             */
/*   Updated: 2025/05/19 06:14:09 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/**
 * Validates the input arguments for the dining philosophers program
 * Converts all arguments to long and stores in an array
 * Sets default value for optional fifth argument if not provided
 * Checks if the number of philosophers is within valid range (1 to MAX)
 * Ensures time-related arguments are non-negative and within INT_MAX
 * Validates the optional "number of meals" argument if present
 * Returns 1 if all checks pass, otherwise returns 0
 */

int	ft_is_valid(char **argv, int argc)
{
	long	args[5];
	int		i;

	i = 1;
	args[0] = ft_atol(argv[1]);
	args[1] = ft_atol(argv[2]);
	args[2] = ft_atol(argv[3]);
	args[3] = ft_atol(argv[4]);
	if (argc == 6)
		args[4] = ft_atol(argv[5]);
	else
		args[4] = 1;
	if (args[0] < 1 || args[0] > MAX)
		return (0);
	while (i < 4)
	{
		if (args[i] < 0 || args[i] > INT_MAX)
			return (0);
		i++;
	}
	if (args[4] < 1 || args[4] > INT_MAX)
		return (0);
	return (1);
}
