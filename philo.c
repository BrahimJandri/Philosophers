/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:50:16 by bjandri           #+#    #+#             */
/*   Updated: 2024/05/28 14:12:14 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;
	int i;
	
	i = -1;
	if (ac == 5 || ac == 6)
	{
		if(!check_int(ac, av))
		{
			init_philos(&data, av);
			free(data.philos);
			free(data.fork_mutex);
			while(++i < data.philo_nb)
				pthread_mutex_destroy(&data.fork_mutex[i]);
		}
	}
	else
		error_input("Usage : 5 800 200 200\n");
	return (0);
}
