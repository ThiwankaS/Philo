/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 04:25:25 by tsomacha          #+#    #+#             */
/*   Updated: 2025/03/18 04:41:58 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_start(t_tabel *table,t_philo **philos, char *argv[], int argc)
{
	int size;
	
	size = ft_atol(argv[1]);
	ft_set_tabel(table, argv, argc);
	*philos = malloc(sizeof(t_philo)*size);
	return (1);
}

int	ft_set_table (t_tabel *table, char *argv[], int argc)
{
	table->is_eaten = 0;
	table->is_eaten = ft_atol(argv[1]);
	return (1);
}
