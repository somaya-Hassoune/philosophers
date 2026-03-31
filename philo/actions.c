/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shassoun <shassoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 23:36:23 by shassoun          #+#    #+#             */
/*   Updated: 2024/11/23 16:52:04 by shassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	__eat(t_program *philo)
{
	pthread_mutex_lock(philo->my_fork);
	if (can_i_write(philo, "has take a fork") == 1)
		return (pthread_mutex_unlock(philo->my_fork), 1);
	pthread_mutex_lock(philo->next_fork);
	if (can_i_write(philo, "has take a fork") == 1)
		return (pthread_mutex_unlock(philo->my_fork), 1);
	if (can_i_write(philo, "is eating") == 1)
		return (pthread_mutex_unlock(philo->my_fork), 1);
	pthread_mutex_lock(philo->meal_mutex);
	philo->last_meal = get_current_time(philo);
	pthread_mutex_unlock(philo->meal_mutex);
	if (ft_sleep(philo->time_to_eat, philo) == 1)
	{
		pthread_mutex_unlock(philo->my_fork);
		pthread_mutex_unlock(philo->next_fork);
		return (1);
	}
	pthread_mutex_unlock(philo->my_fork);
	pthread_mutex_unlock(philo->next_fork);
	return (0);
}

int	__sleeping(t_program *philo)
{
	if (can_i_write(philo, "is sleeping") == 1)
		return (1);
	if (ft_sleep(philo->time_to_sleep, philo) == 1)
		return (1);
	return (0);
}

int	__thinking(t_program *philo)
{
	if (can_i_write(philo, "is thinking") == 1)
		return (1);
	if (philo->time_to_eat >= philo->time_to_sleep)
	{
		if (ft_sleep(philo->time_to_eat - philo->time_to_sleep, philo) == 1)
			return (1);
		usleep(450);
	}
	return (0);
}
