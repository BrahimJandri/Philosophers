/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:19:29 by bjandri           #+#    #+#             */
/*   Updated: 2024/05/30 09:42:39 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	static struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long	get_current_time(t_data *data)
{
	return (get_time() - data->philos->start_time);
}

void	ft_sleep(int time)
{
	long	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(100);
}

int	check_if_dead(t_philo *philo)
{
	if ((get_time() - philo->last_meal) >= philo->data->time_to_die)
	{
		print_status("has died ⚰️", philo);
		pthread_mutex_lock(&philo->data->print_mutex);
		philo->data->die = 1;
		pthread_mutex_unlock(&philo->data->print_mutex);
		return (1);
	}
	return (0);
}

int	check_is_full(t_philo *philo)
{
	usleep(100);
	if (philo->data->number_of_meals == philo->meals_counter)
	{
		return (1);
	}
	return (0);
}
