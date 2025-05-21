/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 05:33:21 by tsomacha          #+#    #+#             */
/*   Updated: 2025/05/21 02:50:57 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/**
 * Function declaration
*/
int		ft_isalive(t_philo *philos, int size);
int		ft_check_meal(t_philo *philos, int size);
void	*observer(void *arg);

/**
 * Checks if all philosophers are still alive
 * Iterates through each philosopher and compares current time with their
 * last meal time
 * If a philosopher has exceeded their allowed time to die,
 * prints "died" message
 * Sets the shared is_alive flag to 0 using mutex to ensure thread safety
 * Returns 0 if any philosopher has died, otherwise returns 1
*/
int	ft_isalive(t_philo *philos, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (getcurrenttime() - philos[i].tm_lst > philos[i].tm_die)
		{
			ft_print(&philos[i], "died");
			pthread_mutex_lock(philos[i].lck_die);
			*philos[i].is_alive = 0;
			pthread_mutex_unlock(philos[i].lck_die);
			return (0);
		}
		i++;
	}
	return (1);
}

/**
 * Checks if all philosophers have eaten the required number of meals
 * Returns 0 immediately if no meal limit is set (meals == -1)
 * Counts how many philosophers have reached or exceeded their meal target
 * If all have finished eating, sets the shared has_eaten flag using mutex
 * Returns 1 if all philosophers are done eating, otherwise returns 0
*/
int	ft_check_meal(t_philo *philos, int size)
{
	int	i;
	int	finished;

	i = 0;
	finished = 0;
	if (philos[0].meals == -1)
		return (0);
	while (i < size)
	{
		if (philos[i].eaten >= philos[i].meals)
			finished++;
		i++;
	}
	if (finished == size)
	{
		pthread_mutex_lock(philos[0].lck_mel);
		*philos[0].has_eaten = 1;
		pthread_mutex_unlock(philos[0].lck_mel);
		return (1);
	}
	return (0);
}

/**
 * Observer thread function to monitor the philosophers
 * Continuously checks if any philosopher has died or if all have
 * finished eating
 * Calls ft_isalive to detect death and ft_check_meal to check
 * meal completion
 * Terminates the loop imidiately and exits the thread when
 * either condition is met
*/
void	*observer(void *arg)
{
	int		size;
	int		flag;
	t_philo	*philos;

	flag = 1;
	philos = (t_philo *) arg;
	size = philos[0].size;
	while (flag)
	{
		if (!ft_isalive(philos, size) || ft_check_meal(philos, size))
			flag = 0;
	}
	return (NULL);
}
