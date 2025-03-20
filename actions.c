/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 04:33:21 by tsomacha          #+#    #+#             */
/*   Updated: 2025/03/20 05:32:49 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_think(t_philo *philo)
{
	int	flag;

	pthread_mutex_lock(philo->lck_die);
	if (!*philo->is_alive)
		flag = 0;
	else
		flag = 1;
	pthread_mutex_unlock(philo->lck_die);
	if (!flag)
		return (0);
	ft_print(philo, "is thinking");
	return (1);
}

int	ft_eat(t_philo *philo)
{
	int		flag;
	size_t	time;

	pthread_mutex_lock(philo->lck_die);
	if (!*philo->is_alive)
		flag = 0;
	else
		flag = 1;
	pthread_mutex_unlock(philo->lck_die);
	if (!flag)
		return (0);
	pthread_mutex_lock(&philo->fork_l->fork);
	ft_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->fork_r->fork);
	ft_print(philo, "has taken a fork");
	time = getcurrenttime();
	philo->tm_lst = time;
	ft_print(philo, "is eating");
	ft_usleep(philo->tm_eat);
	pthread_mutex_unlock(&philo->fork_l->fork);
	pthread_mutex_unlock(&philo->fork_r->fork);
	return (1);
}

int	ft_sleep(t_philo *philo)
{
	int	flag;

	pthread_mutex_lock(philo->lck_die);
	if (!*philo->is_alive)
		flag = 0;
	else
		flag = 1;
	pthread_mutex_unlock(philo->lck_die);
	if (!flag)
		return (0);
	ft_print(philo, "is sleeping");
	ft_usleep(philo->tm_slp);
	return (1);
}
