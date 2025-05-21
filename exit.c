/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 05:36:03 by tsomacha          #+#    #+#             */
/*   Updated: 2025/05/21 02:57:22 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/**
 * Function declaration
*/
int	ft_exit(t_table *table, t_fork *forks, t_philo *philos);

/**
 * Cleans up resources before exiting the program
 * Destroys the mutex used for death detection
 * Frees allocated memory for forks and philosophers if they exist
 * Returns 1 on successful cleanup, 0 if mutex destruction fails
*/
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
