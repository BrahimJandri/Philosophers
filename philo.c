/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:50:16 by bjandri           #+#    #+#             */
/*   Updated: 2024/05/28 10:31:27 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		check_int(ac, av);
		init_philos(&data, av);
		free(data.philos);
		free(data.fork_mutex);
		int i = -1;
		while(++i < data.philo_nb)
			pthread_mutex_destroy(&data.fork_mutex[i]);
	}
	else
		error_input("Usage : 5 800 200 200\n");
}
