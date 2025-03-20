/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 05:36:03 by tsomacha          #+#    #+#             */
/*   Updated: 2025/03/20 05:36:05 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_exit(t_table *table, t_fork *forks, t_philo *philos)
{
	if ((pthread_mutex_destroy(&table->lck_die)) != 0)
		return (0);
	if (forks)
		free(forks);
	if (philos)
		free(philos);
	return (1);
}
