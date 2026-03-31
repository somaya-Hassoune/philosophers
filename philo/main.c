/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shassoun <shassoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:49:21 by shassoun          #+#    #+#             */
/*   Updated: 2024/11/24 23:20:26 by shassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	init_philos(t_program *pr, t_program *philo, int *dead_flag)
{
	int	i;

	i = 0;
	while (i <= pr->number_philo)
	{
		philo[i].number_philo = pr->number_philo;
		philo[i].dead_flag = dead_flag;
		philo[i].time_to_die = pr->time_to_die;
		philo[i].time_to_eat = pr->time_to_eat;
		philo[i].time_to_sleep = pr->time_to_sleep;
		philo[i].number_meals_eated = pr->number_meals_eated;
		philo[i].id = i;
		philo[i].forks = pr->forks;
		philo[i].dead_mutex = &pr->forks[0];
		philo[i].my_fork = &pr->forks[(i)];
		philo[i].next_fork = &pr->forks[((i) % pr->number_philo) + 1];
		philo[i].meal_mutex = &pr->forks[pr->number_philo + 1];
		i++;
	}
	philo[philo->number_philo].my_fork = &pr->forks[1];
	philo[philo->number_philo].next_fork = &pr->forks[philo->number_philo];
}

void	createthread_join_dmutex(pthread_t *philosopher, t_program *pr,
		t_program *philo)
{
	int	i;

	i = 1;
	if (pr->number_philo == 1)
	{
		pthread_create(&philosopher[0], NULL, one_philo, &philo[0]);
		pthread_join(philosopher[0], NULL);
	}
	else
	{
		while (i <= pr->number_philo)
		{
			pthread_create(&philosopher[i], NULL, philo_routine, &philo[i]);
			i++;
		}
		pthread_create(&philosopher[0], NULL, dead_routine, &philo[0]);
		i = -1;
		while (++i <= pr->number_philo)
			pthread_join(philosopher[i], NULL);
	}
	i = -1;
	while (++i <= pr->number_philo)
		pthread_mutex_destroy(&pr->forks[i]);
}

int	check(t_program *p1, pthread_t *p2, pthread_mutex_t *p3)
{
	if (!p1)
	{
		return (1);
	}
	else if (!p2)
	{
		free(p1);
		return (1);
	}
	else if (!p3)
	{
		free(p1);
		free(p2);
		return (1);
	}
	return (0);
}

int	main_suit(t_program *pr)
{
	int				i;
	t_program		*philo;
	pthread_t		*philosopher;
	pthread_mutex_t	*forks;
	int				dead_flag;

	dead_flag = 1;
	i = -1;
	philosopher = malloc((pr->number_philo + 1) * sizeof(pthread_t));
	philo = malloc((pr->number_philo + 1) * sizeof(t_program));
	forks = malloc((pr->number_philo + 3) * sizeof(pthread_mutex_t));
	if (check(philo, philosopher, forks) == 1)
	{
		return (1);
	}
	pr->forks = forks;
	while (++i <= pr->number_philo + 1 + 1)
		pthread_mutex_init(&pr->forks[i], NULL);
	init_philos(pr, philo, &dead_flag);
	define_start_time(philo);
	createthread_join_dmutex(philosopher, pr, philo);
	free(philosopher);
	free(forks);
	free(philo);
	return (0);
}

int	main(int argc, char **argv)
{
	t_program	pr;

	pr.number_philo = ft_atoi(argv[1]);
	if (pr.number_philo == -1 || pr.number_philo == 0)
		return (1);
	pr.time_to_die = ft_atoi(argv[2]);
	if (pr.time_to_die == -1)
		return (1);
	pr.time_to_eat = ft_atoi(argv[3]);
	if (pr.time_to_eat == -1)
		return (1);
	pr.time_to_sleep = ft_atoi(argv[4]);
	if (pr.time_to_sleep == -1)
		return (1);
	if (argc == 6)
	{
		pr.number_meals_eated = ft_atoi(argv[5]);
		if (pr.number_meals_eated == -1 || pr.number_meals_eated == 0)
			return (1);
	}
	else
		pr.number_meals_eated = -1;
	main_suit(&pr);
	return (0);
}
