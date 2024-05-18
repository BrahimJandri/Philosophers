/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 08:56:29 by bjandri           #+#    #+#             */
/*   Updated: 2024/05/18 09:47:29 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    data_init(t_data *data)
{
    int i;

    i = -1;
    data->end = false;
    data->philo_nbr = safe_malloc(sizeof(t_philo) * data->philo_nbr);
    data->forks = safe_malloc(sizeof(t_fork) * data->philo_nbr);
    while (++i < data->philo_nbr)
    {
        pthread_mutex_init(&data->forks[i].fork_id, NULL);
        data->forks[i].fork_id = i;
    }
}