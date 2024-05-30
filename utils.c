/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:19:29 by bjandri           #+#    #+#             */
/*   Updated: 2024/05/30 18:53:18 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	static struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_sleep(int time)
{
	long	start;

	start = get_time();
	while (get_time() - start <= time);
}

int	check_if_dead(t_philo *philo)
{
	if(philo->data->die == 1)
		return (1);
	if (((get_time() - philo->last_meal)) >= philo->data->time_to_die)
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

void *monitoring(void *arg)
{
	int i;
	t_data *data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->philo_nb)
		{
			if (((get_time() - data->philos[i].last_meal)) >= data->time_to_die)
			{
				pthread_mutex_lock(&data->print_mutex);
				data->die = 1;
				pthread_mutex_unlock(&data->print_mutex);
				// print_status("has die\n", data->philos);
				printf("%ld %d has die\n", get_time() - data->philos[i].last_meal, data->philos[i].id);
				return NULL;
			}
			i++;
		}
	}
}