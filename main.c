/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 04:26:37 by tsomacha          #+#    #+#             */
/*   Updated: 2025/03/18 04:37:36 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int main (int argc, char *argv[])
{
	t_tabel table;
	t_philo *philos;

	if(argc == 5 || argc == 6)
	{
		if(ft_is_valid(argv, argc))
		{
			ft_start(&table, &philos, argv, argc);
		}
		else
			ft_error("Invalid arguments!");
	}
	else
		ft_error("Incorrect no of arguments!");
	return (0);
}
