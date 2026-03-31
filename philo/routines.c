/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shassoun <shassoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:49:14 by shassoun          #+#    #+#             */
/*   Updated: 2024/11/24 23:05:58 by shassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	do_action(t_program *philo)
{
	if (__eat(philo) == 1)
		return (1);
	if (__sleeping(philo) == 1)
		return (1);
	if (__thinking(philo) == 1)
		return (1);
	if (philo->number_meals_eated != -1)
		(philo->number_meals_eated)--;
	return (0);
}

int	traitement(t_program *philo, int i, int *count)
{
	long long	k;

	pthread_mutex_lock(philo->meal_mutex);
	k = philo[i].last_meal;
	pthread_mutex_unlock(philo->meal_mutex);
	if (k == -1)
		(*count)--;
	else if (get_current_time(philo) - k > philo->time_to_die)
	{
		pthread_mutex_lock(philo->dead_mutex);
		*(philo->dead_flag) = 0;
		pthread_mutex_unlock(philo->dead_mutex);
		usleep(1000);
		printf("%lld %d is dead \n", get_current_time(philo)
			- philo->start_time, i);
		return (1);
	}
	if ((*count) == 0)
		return (1);
	return (0);
}

void	*dead_routine(void *arg)
{
	int			i;
	t_program	*philo;
	int			count;

	i = 1;
	philo = (t_program *)arg;
	count = philo->number_philo;
	while (philo->start_time > get_current_time(philo))
	{
	}
	philo->start_time = get_current_time(philo);
	usleep(5000);
	while (1)
	{
		if (i == philo->number_philo + 1)
		{
			count = philo->number_philo;
			usleep(1000);
			i = 1;
		}
		if (traitement(philo, i, &count) == 1)
			break ;
		i++;
	}
	return (NULL);
}

void	*one_philo(void *arg)
{
	t_program	*philo;

	philo = (t_program *)arg;
	pthread_mutex_lock(philo->my_fork);
	pthread_mutex_unlock(philo->my_fork);
	ft_sleep(philo->time_to_die, philo);
	printf("%lld %d is dead\n", philo->time_to_die, 1);
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_program	*philo;

	philo = (t_program *)arg;
	while (philo->start_time > get_current_time(philo))
	{
	}
	philo->start_time = get_current_time(philo);
	pthread_mutex_lock(philo->meal_mutex);
	philo->last_meal = philo->start_time;
	pthread_mutex_unlock(philo->meal_mutex);
	if (philo->id % 2 != 0)
	{
		if (ft_sleep(philo->time_to_eat, philo) == 1)
			return (NULL);
	}
	while (philo->number_meals_eated == -1 || philo->number_meals_eated > 0)
	{
		if (do_action(philo) == 1)
			return (NULL);
	}
	pthread_mutex_lock(philo->meal_mutex);
	philo->last_meal = -1;
	pthread_mutex_unlock(philo->meal_mutex);
	return (NULL);
}
