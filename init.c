/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 04:25:25 by tsomacha          #+#    #+#             */
/*   Updated: 2025/03/18 16:19:13 by tsomacha         ###   ########.fr       */
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
	if (!*philo->is_alive)
		return (0);
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

int	ft_life(t_philo *philo)
{
	ft_think(philo);
	ft_eat(philo);
	ft_sleep(philo);
	return (1);
}

void *routine(void *arg)
{
	t_philo *philo = (t_philo *) arg;
	while(*philo->is_alive)
	{
		ft_life(philo);
	}
	return (NULL);
}

void *observer(void *arg)
{
	int i;
	int size;
	t_philo *philos = (t_philo *) arg;
	size = philos[0].size;
	while (true)
	{
		i = 0;
		while (i < size)
		{
			if (getcurrenttime() - philos[i].tm_brn > philos[i].tm_die)
			{
				*philos[i].is_alive = 0;
				break;
			}
			i++;
		}
	}
	return (NULL);
}

int ft_set_table(t_table *table, char *argv[])
{
	table->size = ft_atol(argv[1]);
	table->is_alive = 1;
	return (1);
}

int ft_start(t_table *table, t_philo *philos, char *argv[])
{
	int i;
	int size;
	size_t	time = getcurrenttime();
	ft_set_table(table, argv);
	i = 0;
	size = table->size;
	while(i < size)
	{
		philos[i].id = i + 1;
		philos[i].tm_die = ft_atol(argv[2]);
		philos[i].tm_eat = ft_atol(argv[3]);
		philos[i].tm_slp = ft_atol(argv[4]);
		philos[i].tm_brn = time;
		philos[i].size = size;
		philos[i].is_alive = &table->is_alive;
		i++;
	}

	if ((pthread_create(&table->checker, NULL, observer, philos)) != 0)
		return (0);

	i = 0;
	while (i < size)
	{
		if ((pthread_create(&philos[i].thread, NULL, routine, &philos[i])) != 0)
			return (0);
		i++;
	}

	i = 0;
	while ( i < size)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			return (0);
		i++;
	}

	if (pthread_join(table->checker, NULL) != 0)
		return (0);
	return (1);
}
