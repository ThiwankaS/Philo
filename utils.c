/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 04:15:29 by tsomacha          #+#    #+#             */
/*   Updated: 2025/05/21 03:13:07 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/**
 * Function declaration
*/
int		ft_error(char *text);
int		ft_usleep(size_t m_sec);
int		ft_print(t_philo *philo, char *str);
size_t	ft_strlen(char *str);
size_t	getcurrenttime(void);

/**
 * Displays an error message to standard error output
 * Prepends and appends formatting around the provided error text
 * Returns 1 after writing the message
*/
int	ft_error(char *text)
{
	size_t	len;

	len = ft_strlen(text);
	write(2, " ERROR : [ ", 11);
	write(2, text, len);
	write(2, " ]\n", 3);
	return (1);
}

/**
 * Custom sleep function that pauses execution for a given number of milliseconds
 * Uses a loop to repeatedly sleep in small intervals (500 microseconds)
 * Ensures more accurate timing than standard usleep for short durations
 * Returns 1 after the specified time has passed
*/
int	ft_usleep(size_t m_sec)
{
	size_t	time;

	time = getcurrenttime();
	while (getcurrenttime() - time < m_sec)
		usleep(500);
	return (1);
}

/**
 * Prints a formatted message about a philosopher's action with a timestamp
 * Locks the write mutex to ensure thread-safe output
 * Calculates elapsed time since the simulation started
 * Prints the message only if the philosopher is still alive
 * Unlocks the write mutex and returns 1
*/
int	ft_print(t_philo *philo, char *str)
{
	size_t	time;

	pthread_mutex_lock(philo->lck_wrt);
	time = getcurrenttime() - philo->tm_brn;
	if (ft_has_died(philo))
		printf("%zu %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(philo->lck_wrt);
	return (1);
}

/**
 * Calculates the length of a null-terminated string
 * Returns the number of characters before the null terminator
 * Safely handles a NULL pointer by returning 0
*/
size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

/**
 * Retrieves the current system time in milliseconds
 * Uses gettimeofday to get time in seconds and microseconds
 * Converts the result to milliseconds and returns it
 * Returns 0 if gettimeofday fails
*/
size_t	getcurrenttime(void)
{
	t_timeval	time;
	size_t		m_sec;

	if (gettimeofday(&time, NULL) != 0)
		return (0);
	m_sec = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (m_sec);
}
