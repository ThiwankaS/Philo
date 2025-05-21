/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 02:58:01 by tsomacha          #+#    #+#             */
/*   Updated: 2025/05/21 06:06:12 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/**
 * Function declaration
*/
int		ft_life(t_philo *philo);
int		ft_has_died(t_philo *philo);
int		ft_is_active(t_philo *philo);
void	*routine(void *arg);

/**
 *ft_life function is the main loop which will take each philosopher through
 * his life cycle.
*/
int	ft_life(t_philo *philo)
{
	if (philo->size == 1)
	{
		ft_print(philo, "has taken a fork");
		ft_usleep(philo->tm_die);
		ft_print(philo, "died");
		*philo->is_alive = 0;
		return (1);
	}
	ft_think(philo);
	ft_eat(philo);
	ft_sleep(philo);
	return (1);
}

/**
*ft_flag functio is always check the is_alive value, default value set
*during the initializing statge in '1'. As soon as a philosopher died this
*value set to '0'.
*Synchronizing has made possible using the mutex_lock lck_die.
*/
int	ft_has_died(t_philo *philo)
{
	pthread_mutex_lock(philo->lck_mel);
	pthread_mutex_lock(philo->lck_die);
	if (*philo->is_alive)
	{
		pthread_mutex_unlock(philo->lck_die);
		pthread_mutex_unlock(philo->lck_mel);
		return (1);
	}
	pthread_mutex_unlock(philo->lck_die);
	pthread_mutex_unlock(philo->lck_mel);
	return (0);
}

/**
 * Checks if the philosopher should continue participating in the simulation
 * Uses mutexes to safely read shared flags: is_alive and has_eaten
 * Returns 1 if the philosopher is alive and not all have finished eating
 * Returns 0 otherwise
*/
int	ft_is_active(t_philo *philo)
{
	int	alive;
	int	not_full;

	pthread_mutex_lock(philo->lck_mel);
	pthread_mutex_lock(philo->lck_die);
	alive = *philo->is_alive;
	not_full = !(*philo->has_eaten);
	pthread_mutex_unlock(philo->lck_die);
	pthread_mutex_unlock(philo->lck_mel);
	return (alive && not_full);
}

/**
 * Routine function executed by each philosopher thread
 * Continuously runs the philosopher's life cycle (eating, sleeping, thinking)
 * Loop runs as long as the philosopher has not died and not all have eaten
 * Calls ft_life to perform the philosopher's actions
*/
void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (ft_is_active(philo))
	{
		ft_life(philo);
	}
	return (NULL);
}
