/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 04:04:21 by tsomacha          #+#    #+#             */
/*   Updated: 2025/03/25 06:37:06 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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

/*
** ft_is_valid - Validates command-line arguments for numeric constraints.
**
** This function converts command-line arguments to long integers using ft_atol.
** It then checks if each argument falls within specified numeric constraints:
** - The first argument (args[0]) must be between 1 and MAX.
** - All subsequent arguments must be between 0 and INT_MAX.
** If any argument fails the constraints, the function returns 0 (invalid).
**
** Parameters:
**   argv - Array of command-line argument strings.
**   argc - Number of command-line arguments provided.
**
** Returns:
**   1 if all arguments are valid according to specified constraints,
**   0 if any argument is invalid.
*/
