/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 04:33:21 by tsomacha          #+#    #+#             */
/*   Updated: 2025/03/19 05:10:11 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_think(t_philo *philo)
{
	if (!*philo->is_alive)
		return (0);
	ft_print(philo, "is thinking");
	return (1);
}

int	ft_eat(t_philo *philo)
{
	size_t	time;

	if (!*philo->is_alive)
		return (0);
	//pthread_mutex_lock(&philo->fork_l->fork);
	time = getcurrenttime();
	philo->tm_lst = time;
	ft_print(philo, "is eating");
	ft_usleep(philo->tm_eat);
	return (1);
}

int	ft_sleep(t_philo *philo)
{
	if (!*philo->is_alive)
		return (0);
	ft_print(philo, "is sleeping");
	ft_usleep(philo->tm_slp);
	return (1);
}

