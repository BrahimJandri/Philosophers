/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:24:43 by bjandri           #+#    #+#             */
/*   Updated: 2024/05/26 15:01:01 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	taking_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->print_mutex);
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
	usleep(20000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleep_think(t_philo *philo)
{
	printf("%ld %d is sleeping\n", get_current_time(philo->data), philo->id);
	usleep(20000);
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
		// pthread_mutex_lock(&philo->data->print_mutex);
		// if (philo->data->philo_deid != 0)
		// {
		//     pthread_mutex_unlock(&philo->data->print_mutex);
		//     break ;
		// }
		taking_forks(philo);
		is_eating(philo);
		sleep_think(philo);
	}
	return (NULL);
}

int	check_if_dead(t_philo *philo)
{
	usleep(100);
	if (get_time() - philo->last_meal > philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		philo->data->philo_deid = 1;
		pthread_mutex_unlock(&philo->data->print_mutex);
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%ld %d has died\n", get_current_time(philo->data), philo->id);
		pthread_mutex_unlock(&philo->data->print_mutex);
		return (1);
	}
	return (0);
}
