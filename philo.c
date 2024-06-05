/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:50:16 by bjandri           #+#    #+#             */
/*   Updated: 2024/06/02 13:32:55 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo_args(t_data *data, char **av)
{
	data->philo_nb = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (av[5])
	{
		data->number_of_meals = ft_atol(av[5]);
	}
	else
		data->number_of_meals = -1;
	if (data->number_of_meals == 0 || data->philo_nb == 0)
	{
		printf("ERROR : philo and number of meals must be more than 0\n");
		return (1);
	}
	return (0);
}

void	free_all(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_nb)
		pthread_mutex_destroy(&data->fork_mutex[i]);
	pthread_mutex_destroy(&data->print_mutex);
	free(data->philos);
	free(data->fork_mutex);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		if (check_int(ac, av) || init_philo_args(&data, av))
			return (1);
		if (init_philos(&data))
			free_all(&data);
		free_all(&data);
	}
	else
		error_input("Usage : 5 800 200 200\n");
	return (0);
}
