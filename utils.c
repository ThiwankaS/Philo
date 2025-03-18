/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 04:15:29 by tsomacha          #+#    #+#             */
/*   Updated: 2025/03/18 04:15:31 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int	ft_error(char *text)
{
	size_t	len;

	len = ft_strlen(text);
	write(2, " ERROR : [ ", 11);
	write(2, text, len);
	write(2, " ]\n", 3);
	return (1);
}
