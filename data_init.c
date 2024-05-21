/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 08:56:29 by bjandri           #+#    #+#             */
/*   Updated: 2024/05/21 09:00:15 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    data_init(t_data *data)
{
    int i;

    i = 0;
    data->end = false;
    data->philo_nbr = (long int)malloc(sizeof(t_philo) * data->philo_nbr);
    if(!data->philo_nbr)
        error_input("Malloc Fails in philo number");
    data->forks->fork_id = (long int)malloc(sizeof(t_fork) * data->philo_nbr);
    if(!data->forks->fork_id)
        error_input("Malloc Fails in forks number");
    while (i++ < data->philo_nbr)
    {
        pthread_mutex_init(&data->forks[i].fork, NULL);
        data->forks[i].fork_id = i;
    }
}

void    data_destroy(t_data *data)
{
    int i;

    i = -1;
    while (++i < data->philo_nbr)
        pthread_mutex_destroy(&data->forks[i].fork);
    free(&data->philo_nbr);
    free(data->forks);
}

void    philo_init(t_data *data)
{
    int i;

    i = -1;
    while (++i < data->philo_nbr)
    {
        data->philos[i].id = i;
        data->philos[i].last_meal = get_time();
        data->philos[i].data = data;
    }
}

void    philo_destroy(t_data *data)
{
    free(data->philos);
}

void    philo_create(t_data *data)
{
    int i;

    i = -1;
    while (++i < data->philo_nbr)
        pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]);
}

void    philo_join(t_data *data)
{
    int i;

    i = -1;
    while (++i < data->philo_nbr)
        pthread_join(data->philos[i].thread, NULL);
}

