/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:08:58 by bjandri           #+#    #+#             */
/*   Updated: 2024/05/23 16:50:28 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	main(int ac, char **av)
{
	t_data data;
	
	if (ac == 5 || ac == 6)
	{
		check_int(ac, av);
		init_args(&data, av);
		init_philo(&data);
		forks_creat(&data);
		start_philo_routine(&data);
	}
	else
		error_input("usage : ./philo 5 800 200 200");
	return (0);
}
