/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 04:33:21 by tsomacha          #+#    #+#             */
/*   Updated: 2025/05/21 07:42:17 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/**
 * Function declarations
*/
int		ft_think(t_philo *philo);
int		ft_eat(t_philo *philo);
int		ft_sleep(t_philo *philo);

/**
 * philosopher's think routine function
*/
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
*/
int	ft_eat(t_philo *philo)
{
	size_t			time;

	if (philo->size > 1)
	{
		if (pthread_mutex_lock(&philo->fork_l->fork) != 0)
			return (1);
		ft_print(philo, "has taken a fork");
		if (pthread_mutex_lock(&philo->fork_r->fork) != 0)
			return (pthread_mutex_unlock(&philo->fork_l->fork), 1);
		ft_print(philo, "has taken a fork");
		pthread_mutex_lock(philo->lck_mel);
		time = getcurrenttime();
		philo->tm_lst = time;
		philo->eaten++;
		pthread_mutex_unlock(philo->lck_mel);
		ft_print(philo, "is eating");
		ft_usleep(philo->tm_eat);
		pthread_mutex_unlock(&philo->fork_r->fork);
		pthread_mutex_unlock(&philo->fork_l->fork);
		return (1);
	}
	else
		return (0);
}

/**
 * philosopher's sleep routine function
*/
int	ft_sleep(t_philo *philo)
{
	ft_print(philo, "is sleeping");
	ft_usleep(philo->tm_slp);
	return (1);
}
