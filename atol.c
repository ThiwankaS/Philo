/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atol.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 03:31:49 by tsomacha          #+#    #+#             */
/*   Updated: 2025/05/21 02:56:53 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/**
 * Function declaration
*/
long	ft_atol(const char *nptr);

/**
 * Converts a string to a long integer (similar to atoi but returns long)
 * Skips leading whitespace characters
 * Handles optional '+' or '-' sign to determine the number's sign
 * Parses digits and builds the numeric result
 * Returns the signed result if the string ends properly
 * Returns an invalid value (greater than INT_MAX) if non-digit characters remain
*/
long	ft_atol(const char *nptr)
{
	int			count;
	int			sign;
	long long	result;

	count = 0;
	sign = 1;
	result = 0;
	while (nptr[count] == ' ' || (nptr[count] >= 9 && nptr[count] <= 13))
		count++;
	if (nptr[count] == '-' || nptr[count] == '+')
	{
		if (nptr[count] == '-')
			sign = -1;
		count++;
	}
	while (nptr[count] >= '0' && nptr[count] <= '9')
	{
		result = result * 10 + (nptr[count] - '0');
		count++;
	}
	if (!nptr[count])
		return ((result * sign));
	else
		return (result + INT_MAX + 1);
}
