/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shassoun <shassoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:48:44 by shassoun          #+#    #+#             */
/*   Updated: 2024/11/23 16:58:42 by shassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_program
{
	long long		last_meal;
	long long		start_time;
	int				id;
	int				number_philo;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				number_meals_eated;
	int				*dead_flag;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*my_fork;
	pthread_mutex_t	*next_fork;
	pthread_mutex_t	*dead_mutex;
	pthread_mutex_t	*meal_mutex;
}					t_program;

long				ft_atoi(char *str);
long long			get_current_time(t_program *philo);
int					ft_sleep(long long ttime, t_program *philo);
void				*one_philo(void *arg);
void				*philo_routine(void *arg);
void				*dead_routine(void *arg);
int					can_i_write(t_program *philo, char *str);
void				define_start_time(t_program *philo);
int					__eat(t_program *philo);
int					__sleeping(t_program *philo);
int					__thinking(t_program *philo);

#endif