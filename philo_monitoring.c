/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitoring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:45:56 by bjandri           #+#    #+#             */
/*   Updated: 2024/05/24 16:23:07 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_last_meal(t_philo *philo)
{
	if (get_time() - philo->start_time > philo->data->time_to_die)
	{
		philo->philo_deid = 1;
		printf("%ld %d died\n", get_time()
			- philo->start_time, philo->id);
		return (0);
	}
	else
		return (1);
}

int	check_if_one_is_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		if (check_last_meal(&data->philos[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	free_philo(t_data *data)
{
	free(data->philos);
}

void	*start_monitoring(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		pthread_mutex_lock(&data->philos->philo_mutex);
		if (check_if_one_is_dead(data) == 0)
		{
			usleep(100);
			return (pthread_mutex_unlock(&data->philos->philo_mutex), NULL);
		}
		pthread_mutex_unlock(&data->philos->philo_mutex);
		usleep(200);
	}
}