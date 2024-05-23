/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 08:56:11 by bjandri           #+#    #+#             */
/*   Updated: 2024/05/23 10:01:57 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (philo->philo_deid == 0) 
    {
        if(philo_is_dead(philo))
            return (0);
        philo_takes_forks(philo);
        	if (philo_is_dead(philo))
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			return (0);
		}
		philo_is_eating(philo);
		if (philo_is_dead(philo))
			return (0);
		philo_is_sleeping(philo);
		if (philo_is_dead(philo))
			return (0);
		philo_is_thinking(philo);
	}
	return (0);
}


void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nbr)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

void	begin_philosophers_routine(t_data *data)
{
	int	i;

	i = 0;
	data->philos->start_time = get_time();
	while (i < data->philo_nbr)
	{
		pthread_create(&data->philos[i].thread,
			NULL, &philo_routine, (void *)&data->philos[i]);
		i++;
	}
	i = 0;
	while (i < data->philo_nbr)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}