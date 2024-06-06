/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:19:29 by bjandri           #+#    #+#             */
/*   Updated: 2024/06/06 10:20:21 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	static struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_sleep(long times)
{
	time_t	start_time;

	start_time = get_time();
	while (get_time() - start_time < times)
		usleep(100);
}

int	check_if_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if ((get_time() - philo->last_meal) > philo->data->time_to_die)
	{
		pthread_mutex_unlock(&philo->data->print_mutex);
		pthread_mutex_lock(&philo->data->print_mutex);
		philo->data->die = 1;
		pthread_mutex_unlock(&philo->data->print_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
	return (0);
}

int	check_is_full(t_data *data)
{
	int i; 
	
	i = 0;
	while(i < data->philo_nb)
	{
		pthread_mutex_lock(&data->print_mutex);
		if (data->number_of_meals != data->philos[i].meals_counter)
		{
			pthread_mutex_unlock(&data->print_mutex);
			return (0);
		}
		pthread_mutex_unlock(&data->print_mutex);
		i++;
	}
	pthread_mutex_lock(&data->print_mutex);
	data->is_full = 1;
	pthread_mutex_unlock(&data->print_mutex);
	return (1);
}

void	*monitoring(void *arg)
{
	int		i;
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		i = -1;
		while (++i < data->philo_nb)
		{
			if (check_is_full(data) == 1 || data->die == 1)
				return (NULL);
			pthread_mutex_lock(&data->print_mutex);
			if ((get_time() - data->philos[i].last_meal) > data->time_to_die)
			{
				pthread_mutex_unlock(&data->print_mutex);
				print_status("has died ⚰️", &data->philos[i]);
				pthread_mutex_lock(&data->print_mutex);
				data->die = 1;
				pthread_mutex_unlock(&data->print_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&data->print_mutex);
		}
	}
}
