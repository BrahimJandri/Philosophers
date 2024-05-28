/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:24:43 by bjandri           #+#    #+#             */
/*   Updated: 2024/05/28 10:40:16 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	taking_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status("has taking a right fork", philo);
		pthread_mutex_lock(philo->left_fork);
		print_status("has taking a left fork", philo);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_status("has taking a left fork", philo);
		pthread_mutex_lock(philo->right_fork);
		print_status("has taking a right fork", philo);
	}
}
void	print_status(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock_mutex);
	if (philo->data->die)
	{
		pthread_mutex_unlock(&philo->data->lock_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->lock_mutex);
	printf("%ld %d %s\n", get_current_time(philo->data), philo->id, str);
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
	pthread_mutex_lock(&philo->data->print_mutex);
	print_status("is sleeping 😴", philo);
	pthread_mutex_unlock(&philo->data->print_mutex);
	usleep(philo->data->time_to_sleep);
	pthread_mutex_lock(&philo->data->print_mutex);
	print_status("is thinking 🤔", philo);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!check_if_dead(philo))
	{
		taking_forks(philo);
		is_eating(philo);
		sleep_think(philo);
	}
	return (NULL);
}

int	check_if_dead(t_philo *philo)
{
	usleep(100);
	if ((get_time() - philo->last_meal) >= philo->data->time_to_die)
	{
		
		pthread_mutex_lock(&philo->data->print_mutex);
		print_status("has died", philo);
		pthread_mutex_unlock(&philo->data->print_mutex);
		pthread_mutex_lock(&philo->data->lock_mutex);
		philo->data->die = 1;
		pthread_mutex_unlock(&philo->data->lock_mutex);
		return (1);
	}
	return (0);
}
