/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 08:56:11 by bjandri           #+#    #+#             */
/*   Updated: 2024/05/24 16:03:16 by bjandri          ###   ########.fr       */
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
			// pthread_mutex_unlock(philo->left_fork);
			// pthread_mutex_unlock(philo->right_fork);
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


void	start_philo_routine(t_philo *philo)
{
	int	i;

	i = 0;
	philo->start_time = get_time();
	while (i < philo->data->philo_nb)
	{
		pthread_create(&philo[i].thread_id, NULL, &philo_routine, (void *)&philo[i]);
		i++;
	}
	i = 0;
	while (i < philo->data->philo_nb)
	{
		pthread_join(philo[i].thread_id, NULL);
		i++;
	}
}