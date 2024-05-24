/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:01:04 by bjandri           #+#    #+#             */
/*   Updated: 2024/05/24 15:58:30 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int philo_takes_forks(t_philo *philo)
{
	pthread_mutex_t *first_fork, *second_fork;

	if (philo->data->philo_nb % 2 == 0)
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	else
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	pthread_mutex_lock(first_fork);
	if (!philo_is_dead(philo))
		print_msg("has taken a fork", philo);

	pthread_mutex_lock(second_fork);
	if (!philo_is_dead(philo))
		print_msg("has taken a fork", philo);
	return 0;
}

void	philo_is_eating(t_philo *philo)
{
	print_msg("is eating", philo);
	// pthread_mutex_lock(&philo->philo_mutex);
	philo->last_meal = get_time() - philo->start_time;
	philo->data->time_to_die = philo->last_meal + philo->data->time_to_die;
	// pthread_mutex_unlock(&philo->philo_mutex);
	ft_sleep(philo->data->time_to_eat, philo);
	// pthread_mutex_lock(&philo->philo_mutex);
	if (philo->data->number_of_meals != -1)
		philo->meals_counter++;
	// pthread_mutex_unlock(&philo->philo_mutex);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

int philo_is_dead(t_philo *philo)
{
    // pthread_mutex_lock(&philo->philo_mutex);
    if(philo->philo_deid == 1)
    {
        // pthread_mutex_unlock(&philo->philo_mutex);
        return (1);
    }
    // pthread_mutex_unlock(&philo->philo_mutex);
    return (0);
}
void	philo_is_sleeping(t_philo *philo)
{
	print_msg("is sleeping", philo);
	ft_sleep(philo->data->time_to_sleep, philo);
}

void	philo_is_thinking(t_philo *philo)
{
	print_msg("is thinking", philo);
}
