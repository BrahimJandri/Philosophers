/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 08:56:29 by bjandri           #+#    #+#             */
/*   Updated: 2024/05/22 12:27:34 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void data_init(t_data *data)
{
    int i;

    data->end = false;
    data->philos = (t_philo *)malloc(sizeof(t_philo) * data->philo_nbr);
    if (!data->philos)
        error_input("Malloc Fails in philo number");
    data->forks = (t_fork *)malloc(sizeof(t_fork) * data->philo_nbr);
    if (!data->forks)
        error_input("Malloc Fails in forks number");

    pthread_mutex_init(&data->data_mutex, NULL);
    i = 0;
    while (i < data->philo_nbr)
    {
        pthread_mutex_init(&data->forks[i].fork, NULL);
        data->forks[i].fork_id = i;
        i++;
    }
}


void    data_destroy(t_data *data)
{
    int i;

    i = -1;
    while (++i < data->philo_nbr)
        pthread_mutex_destroy(&data->forks[i].fork);
    free(data->philos);
    free(data->forks);
}

void    philo_init(t_data *data)
{
    int i;

    i = -1;
    while (++i < data->philo_nbr)
    {
        data->philos[i].id = i + 1;
        data->philos[i].last_meal = get_time();
        data->philos[i].full = false;
        data->philos[i].meals_counter = 0;
        data->philos[i].data = data;
        data->philos->deid = false;
        data->philos[i].right_fork = &data->forks[i].fork;
        data->philos[i].left_fork = &data->forks[(i + 1) % data->philo_nbr].fork;
    }
}


void    philo_create(t_data *data)
{
    int i;

    i = 0;
    data->dinner_start = get_time();
    while (i < data->philo_nbr)
    {
        pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]);
        i++;   
    }
}

void    philo_join(t_data *data)
{
    int i;

    i = 0;
    while (i < data->philo_nbr)
    {
        pthread_join(data->philos[i].thread, NULL);
        i++;   
    }
}

