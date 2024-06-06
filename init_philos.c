/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:04:36 by bjandri           #+#    #+#             */
/*   Updated: 2024/06/06 10:49:04 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_nb)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL, philo_routine,
				(void *)&data->philos[i]))
			return (thread_fail("pthread create fail\n"), 1);
	}
	if (pthread_create(&data->moni, NULL, monitoring, data))
		return (thread_fail("pthread create fail\n"), 1);
	if (pthread_join(data->moni, NULL))
		thread_fail("pthread_join failed\n");
	i = -1;
	while (++i < data->philo_nb)
	{
		if (pthread_join(data->philos[i].thread_id, NULL))
			return (thread_fail("pthread_join failed\n"), 1);
	}
	return (0);
}

int	create_forks(t_data *data)
{
	int	i;

	i = 0;
	data->fork_mutex = malloc(sizeof(pthread_mutex_t) * data->philo_nb);
	if (!data->fork_mutex)
		return (error_input("malloc forks fails\n"), 1);
	pthread_mutex_init(&data->print_mutex, NULL);
	while (i < data->philo_nb)
	{
		if (pthread_mutex_init(&data->fork_mutex[i], NULL) != 0)
			return (error_input("pthread_mutex_init failed\n"), 1);
		i++;
	}
	return (0);
}

int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	if (create_forks(data))
		return (1);
	data->philos = malloc(sizeof(t_philo) * data->philo_nb);
	if (!data->philos)
		error_input("malloc philo fails\n");
	data->die = 0;
	data->is_full = 0;
	while (i < data->philo_nb)
	{
		data->philos[i].is_full = 0;
		data->philos[i].start_time = get_time();
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = &data->fork_mutex[i];
		data->philos[i].right_fork = &data->fork_mutex[(i + 1)
			% data->philo_nb];
		data->philos[i].last_meal = get_time();
		data->philos[i].meals_counter = 0;
		data->philos[i].data = data;
		i++;
	}
	if (create_philos(data))
		return (1);
	return (0);
}
