/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:24:43 by bjandri           #+#    #+#             */
/*   Updated: 2024/05/26 15:30:49 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	taking_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		printf("%ld %d has taking a right fork\n",
			get_current_time(philo->data), philo->id);
		pthread_mutex_lock(philo->left_fork);
		printf("%ld %d has taking a left fork\n", get_current_time(philo->data),
			philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		printf("%ld %d has taking a left fork\n", get_current_time(philo->data),
			philo->id);
		pthread_mutex_lock(philo->right_fork);
		printf("%ld %d has taking a right fork\n",
			get_current_time(philo->data), philo->id);
	}
}

void	is_eating(t_philo *philo)
{
	printf("%ld %d is eating\n", get_current_time(philo->data), philo->id);
	philo->last_meal = get_time();
	usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleep_think(t_philo *philo)
{
	printf("%ld %d is sleeping\n", get_current_time(philo->data), philo->id);
	usleep(philo->data->time_to_sleep);
	printf("%ld %d is thinking\n", get_current_time(philo->data), philo->id);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		taking_forks(philo);
        philo->last_meal = get_time();
		is_eating(philo);
        philo->last_meal = get_time();
        philo->meals_counter++;
		sleep_think(philo);
	}
	return (NULL);
}

void	check_if_dead(t_philo *philo)
{
	usleep(100);
	if (get_time() - philo->last_meal > philo->data->time_to_die || philo->data->number_of_meals == philo->meals_counter)
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		philo->data->philo_deid = 1;
		pthread_mutex_unlock(&philo->data->print_mutex);
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%ld %d has died\n", get_current_time(philo->data), philo->id);
		pthread_mutex_unlock(&philo->data->print_mutex);
        exit(EXIT_FAILURE);
	}
}
