/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:04:36 by bjandri           #+#    #+#             */
/*   Updated: 2024/05/26 14:24:30 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo_args(t_data *data, char **av)
{
	data->philo_nb = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]) * 1000;
	data->time_to_eat = ft_atol(av[3]) * 1000;
	data->time_to_sleep = ft_atol(av[4]) * 1000;
	if (av[5])
		data->number_of_meals = ft_atol(av[5]);
	else
		data->number_of_meals = -1;
}

void	create_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philos->start_time = get_time();
	while (i < data->philo_nb)
	{
		pthread_create(&data->philos[i].thread_id, NULL, philo_routine,
			(void *)&data->philos[i]);
		i++;
	}
	// check_if_dead(data->philos);
	i = 0;
	while (i < data->philo_nb)
	{
		pthread_join(data->philos[i].thread_id, NULL);
		i++;
	}
}

void	create_forks(t_data *data)
{
	int	i;

	i = 0;
	data->fork_mutex = malloc(sizeof(pthread_mutex_t) * data->philo_nb);
	if (!data->fork_mutex)
		error_input("malloc forks fails\n");
	pthread_mutex_init(&data->print_mutex, NULL);
	while (i < data->philo_nb)
	{
		pthread_mutex_init(&data->fork_mutex[i], NULL);
		i++;
	}
}

void	init_philos(t_data *data, char **av)
{
	int	i;

	init_philo_args(data, av);
	create_forks(data);
	data->philos = malloc(sizeof(t_philo) * data->philo_nb);
	if (!data->philos)
		error_input("malloc philo fails\n");
	i = 0;
	data->philo_deid = 0;
	while (i < data->philo_nb)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = &data->fork_mutex[i];
		data->philos[i].right_fork = &data->fork_mutex[(i + 1)
			% data->philo_nb];
		data->philos[i].is_eating = 0;
		data->philos[i].data = data;
		i++;
	}
	create_philos(data);
}
