/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:08:58 by bjandri           #+#    #+#             */
/*   Updated: 2024/05/23 16:15:14 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_init(t_data *data)
{
	int	i;

	i = -1;
	data->fork_mutex
		= malloc(sizeof(pthread_mutex_t) * data->philo_nb);
	if (!data->fork_mutex)
		return (0);
	while (++i < data->philo_nb)
		pthread_mutex_init(&data->fork_mutex[i], NULL);
	pthread_mutex_init(&data->philos->philo_mutex, NULL);
	return (1);
}

int	main(int ac, char **av)
{
	t_data data;
	
	if (ac == 5 || ac == 6)
	{
		check_int(ac, av);
		init_philo(&data);
		start_philo_routine(&data);
	}
	else
		error_input("usage : ./philo 5 800 200 200");
	return (0);
}
