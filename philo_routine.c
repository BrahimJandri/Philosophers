/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:24:43 by bjandri           #+#    #+#             */
/*   Updated: 2024/06/01 09:59:45 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	taking_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status("has taken a fork 🍴", philo);
		pthread_mutex_lock(philo->right_fork);
		print_status("has taken a fork 🍴", philo);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_status("has taken a fork 🍴", philo);
		pthread_mutex_lock(philo->left_fork);
		print_status("has taken a fork 🍴", philo);
	}
}

void	print_status(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (philo->data->die)
	{
		pthread_mutex_unlock(&philo->data->print_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
	printf(BLUE "%ld %d %s\n", (get_time() - philo->start_time), philo->id, str);
}

void	is_eating(t_philo *philo)
{
	print_status("is eating 🍝", philo);
	pthread_mutex_lock(&philo->data->print_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->print_mutex);

	pthread_mutex_lock(&philo->data->print_mutex);
	philo->meals_counter++;
	pthread_mutex_unlock(&philo->data->print_mutex);

	ft_sleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleep_think(t_philo *philo)
{
	print_status("is sleeping 😴", philo);
	ft_sleep(philo->data->time_to_sleep);
	print_status("is thinking 🤔", philo);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	
	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (check_if_dead(philo) || check_is_full(philo))
			return (NULL);
		if (philo->data->philo_nb == 1)
		{
			print_status("has taken a left fork", philo);
			ft_sleep(philo->data->time_to_die + 5);
			continue ;
		}
		taking_forks(philo);
		is_eating(philo);
		sleep_think(philo);
	}
	return (NULL);
}
