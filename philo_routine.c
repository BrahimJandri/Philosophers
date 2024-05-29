/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:24:43 by bjandri           #+#    #+#             */
/*   Updated: 2024/05/29 18:47:36 by bjandri          ###   ########.fr       */
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
	else
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
	if (philo->data->die)
	{
		pthread_mutex_unlock(&philo->data->print_mutex);
		return ;
	}
	if (!philo->data->die)
		printf(WHT"%ld %d %s\n", get_current_time(philo->data), philo->id, str);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	is_eating(t_philo *philo)
{
	print_status("is eating 🍝", philo);
	philo->last_meal = get_time();
    philo->meals_counter++;
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

int	check_if_dead(t_philo *philo)
{
	// usleep(100);
	// printf("to die: %ld die: %d\n", get_current_time(philo->data) - (philo->last_meal - philo->start_time), philo->data->time_to_die);
	if ((get_time() - philo->last_meal) >= philo->data->time_to_die)
	{
		print_status("has died", philo);
		pthread_mutex_lock(&philo->data->print_mutex);
		philo->data->die = 1;
		pthread_mutex_unlock(&philo->data->print_mutex);
		// pthread_mutex_lock(&philo->data->print_mutex);
		// printf("%ld %d has died\n", get_current_time(philo->data), philo->id);
		// pthread_mutex_unlock(&philo->data->print_mutex);
		return 1;
	}
	return 0;
}

void ft_sleep(long time)
{
	long start = get_time();
	while(get_time() - start < time);
}

int check_is_full(t_philo *philo)
{
	usleep(100);
	if (philo->data->number_of_meals == philo->meals_counter)
	{
		// pthread_mutex_lock(&philo->data->print_mutex);
		// printf("Every Philosopher had %d meals!\n", philo->data->number_of_meals);
		// pthread_mutex_unlock(&philo->data->print_mutex);
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
		// printf("%d\n", philo->data->philo_nb);
		if (philo->data->philo_nb == 1)
		{
			print_status("has taken a left fork", philo);
			ft_sleep(philo->data->time_to_die + 4);
			continue;
		}
		taking_forks(philo);
		is_eating(philo);
		sleep_think(philo);	
	}
	return NULL;
}
