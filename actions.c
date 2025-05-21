/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 04:33:21 by tsomacha          #+#    #+#             */
/*   Updated: 2025/05/21 06:08:47 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/**
 * Function declarations
*/
int		ft_think(t_philo *philo);
int		ft_eat(t_philo *philo);
int		ft_sleep(t_philo *philo);
void	order(t_philo *philo, pthread_mutex_t **l1, pthread_mutex_t **l2);

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
	pthread_mutex_t	*l1;
	pthread_mutex_t	*l2;

	if (philo->size > 1)
	{
		order(philo, &l1, &l2);
		pthread_mutex_lock(l1);
		ft_print(philo, "has taken a fork");
		pthread_mutex_lock(l2);
		ft_print(philo, "has taken a fork");
		pthread_mutex_lock(philo->lck_mel);
		time = getcurrenttime();
		philo->tm_lst = time;
		philo->eaten++;
		pthread_mutex_unlock(philo->lck_mel);
		ft_print(philo, "is eating");
		ft_usleep(philo->tm_eat);
		pthread_mutex_unlock(l2);
		pthread_mutex_unlock(l1);
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

void	order(t_philo *philo, pthread_mutex_t **l1, pthread_mutex_t **l2)
{
	if (&philo->fork_l->fork < &philo->fork_r->fork)
	{
		*l1 = &philo->fork_l->fork;
		*l2 = &philo->fork_r->fork;
	}
	else
	{
		*l1 = &philo->fork_r->fork;
		*l2 = &philo->fork_l->fork;
	}
}
