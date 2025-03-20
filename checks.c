/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 05:33:21 by tsomacha          #+#    #+#             */
/*   Updated: 2025/03/20 05:35:30 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_isalive(t_philo *philos, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (getcurrenttime() - philos[i].tm_lst > philos[i].tm_die)
		{
			pthread_mutex_lock(philos[i].lck_die);
			*philos[i].is_alive = 0;
			pthread_mutex_unlock(philos[i].lck_die);
			return (0);
		}
		i++;
	}
	return (1);
}

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
		if (!ft_isalive(philos, size))
			flag = 0;
	}
	return (NULL);
}
