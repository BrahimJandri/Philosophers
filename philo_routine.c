/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:24:43 by bjandri           #+#    #+#             */
/*   Updated: 2024/05/29 15:28:28 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	taking_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status("has taken a right fork", philo);
		pthread_mutex_lock(philo->left_fork);
		print_status("has taken a left fork", philo);
	}
	else if(philo->id % 2 != 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status("has taken a left fork", philo);
		pthread_mutex_lock(philo->right_fork);
		print_status("has taken a right fork", philo);
	}
}

void	print_status(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (philo->die == 0)
	{
		printf("%ld %d %s\n", get_current_time(philo->data), philo->id, str);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	is_eating(t_philo *philo)
{
	print_status("is eating 🍝", philo);
	philo->last_meal = get_time();
    philo->meals_counter++;
	usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleep_think(t_philo *philo)
{
	print_status("is sleeping 😴", philo);
	usleep(philo->data->time_to_sleep);
	print_status("is thinking 🤔", philo);
}

int	check_if_dead(t_philo *philo)
{
	usleep(100);
	if ((get_time() - philo->last_meal) >= philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->lock_mutex);
		philo->die = 1;
		pthread_mutex_unlock(&philo->data->lock_mutex);
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%ld %d has died\n", get_current_time(philo->data), philo->id);
		pthread_mutex_unlock(&philo->data->print_mutex);
		return 1;
	}
	return 0;
}

int check_is_full(t_philo *philo)
{
	usleep(100);
	if (philo->data->number_of_meals == philo->meals_counter)
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("Every Philosopher had %d meals!\n", philo->data->number_of_meals);
		pthread_mutex_unlock(&philo->data->print_mutex);
		return 1;
	}
	return 0;
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	philo = (t_philo *)arg;

	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		if (check_if_dead(philo) || check_is_full(philo))
			return NULL;
		taking_forks(philo);
		is_eating(philo);
		sleep_think(philo);	
	}
	return NULL;
}
