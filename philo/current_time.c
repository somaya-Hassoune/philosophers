/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   current_time.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shassoun <shassoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:49:35 by shassoun          #+#    #+#             */
/*   Updated: 2024/11/23 16:56:38 by shassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long long	get_current_time(t_program *philo)
{
	long long		k;
	struct timeval	tv;

	pthread_mutex_lock(&philo->forks[philo->number_philo + 2]);
	gettimeofday(&tv, NULL);
	k = (long long)(tv.tv_sec * 1000 + tv.tv_usec / 1000);
	pthread_mutex_unlock(&philo->forks[philo->number_philo + 2]);
	return (k);
}

void	define_start_time(t_program *philo)
{
	int	i;

	i = 0;
	philo[0].start_time = get_current_time(philo) + (philo->number_philo * 30);
	while (i <= philo->number_philo)
	{
		philo[i].start_time = philo[0].start_time;
		i++;
	}
}

int	ft_sleep(long long ttime, t_program *philo)
{
	long long	k;

	k = get_current_time(philo);
	while (get_current_time(philo) - k < ttime)
	{
		pthread_mutex_lock(philo->dead_mutex);
		if (*(philo->dead_flag) == 0)
		{
			pthread_mutex_unlock(philo->dead_mutex);
			return (1);
		}
		pthread_mutex_unlock(philo->dead_mutex);
		usleep(100);
	}
	return (0);
}

int	can_i_write(t_program *philo, char *str)
{
	pthread_mutex_lock(philo->dead_mutex);
	if (*(philo->dead_flag) == 0)
	{
		pthread_mutex_unlock(philo->dead_mutex);
		return (1);
	}
	else
		printf("%lld %d %s\n", get_current_time(philo)
			- philo->start_time, philo->id, str);
	pthread_mutex_unlock(philo->dead_mutex);
	return (0);
}
