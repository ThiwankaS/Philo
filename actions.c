/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 04:33:21 by tsomacha          #+#    #+#             */
/*   Updated: 2025/03/25 10:08:57 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/**
 * philosopher's think routine function
 * **/

int	ft_think(t_philo *philo)
{
	ft_print(philo, "is thinking");
	return (1);
}

/**
 * Philosopher's eat routine function. every philosopher first grab the left fork
 * and then the right fork.Synchronization has achieved by implementing forks as
 * mutex_locks.Meal time is updated using getcurrenttime, the meal time
 * considered to be the starting time of eating.
 * **/

int	ft_eat(t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->fork_l->fork);
	ft_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->fork_r->fork);
	ft_print(philo, "has taken a fork");
	pthread_mutex_lock(philo->lck_mel);
	time = getcurrenttime();
	philo->tm_lst = time;
	philo->eaten++;
	pthread_mutex_unlock(philo->lck_mel);
	ft_print(philo, "is eating");
	ft_usleep(philo->tm_eat);
	pthread_mutex_unlock(&philo->fork_l->fork);
	pthread_mutex_unlock(&philo->fork_r->fork);
	return (1);
}

/**
 * philosopher's sleep routine function
 * **/

int	ft_sleep(t_philo *philo)
{
	ft_print(philo, "is sleeping");
	ft_usleep(philo->tm_slp);
	return (1);
}
