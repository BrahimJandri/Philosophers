/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:50:16 by bjandri           #+#    #+#             */
/*   Updated: 2024/06/02 12:42:45 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void free_all(t_data *data)
{
	int		i;
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
		if (check_int(ac, av))
			return (1);
		if(init_philos(&data, av))
			free_all(&data);
	}
	else
		error_input("Usage : 5 800 200 200\n");
	free_all(&data);
	return (0);
}
