/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 05:33:21 by tsomacha          #+#    #+#             */
/*   Updated: 2025/03/27 05:48:15 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/**
 *ft_isalive function call inside obserever thread and continuouly check the
 *last_meal_time against the time_to_die. if (current_time - last_meal_time) is
 *greater than time_to_die meaning the philosppher is already passed the
 *time_to_die limit starving, the respective philospher need to die. The message
 *will print to the terminal immidiatly and is_alive varibale set to '0'
 **/

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
 * observer function is the routine fuction invoke inside observer therad. Both
 * ft_isalive and ft_haseaten helper functions will call inside this to check
 * the both program terminating situations.
 **/

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
