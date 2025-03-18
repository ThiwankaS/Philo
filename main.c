/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 04:26:37 by tsomacha          #+#    #+#             */
/*   Updated: 2025/03/18 15:58:55 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int main (int argc, char *argv[])
{
	int		size;
	t_philo *philos;
	t_table table;

	if(argc == 5 || argc == 6)
	{
		if(ft_is_valid(argv, argc))
		{
			size = ft_atol(argv[1]);
			philos = malloc(sizeof(t_philo)*size);
			if (!philos)
				return (0);
			ft_start(&table, philos, argv);
		}
		else
			ft_error("Invalid arguments!");
	}
	else
		ft_error("Incorrect no of arguments!");
	return (0);
}
