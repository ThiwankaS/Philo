/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atol.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 03:31:49 by tsomacha          #+#    #+#             */
/*   Updated: 2025/03/18 03:34:09 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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
/*
** ft_atol - Converts a string representation of a number to a long integer.
**
** This function skips any initial whitespace characters(space,tab,newline,etc.),
** handles an optional leading '+' or '-' sign, and converts the following digit
** characters into a numeric long integer. If non-digit characters appear before
** reaching the end of the string, the function indicates overflow by returning
** a value larger than INT_MAX.
**
** Parameters:
**   nptr - Pointer to the string to be converted.
**
** Returns:
**   The numeric value represented by the string, adjusted by sign,
**   or an overflow indicating the input is invalid.
*/
