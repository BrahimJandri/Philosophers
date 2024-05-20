/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 09:10:40 by bjandri           #+#    #+#             */
/*   Updated: 2024/05/18 12:15:34 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long    get_time(void)
{
    struct timeval  tv;
    long            time;

    gettimeofday(&tv, NULL);
    time = tv.tv_sec * 1000;
    time += tv.tv_usec / 1000;
    return (time);
}

void *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (!philo->data->end)
    {
        pthread_mutex_lock(&philo->data->forks[philo->left_fork->fork_id].fork);
        pthread_mutex_lock(&philo->data->forks[philo->right_fork->fork_id].fork);
        philo->eating = 1;
        philo->last_meal = get_time();
        philo->meals_counter++;
        printf("%ld %d is eating\n", get_time(), philo->id);
        usleep(philo->data->time_to_eat * 1000);
        pthread_mutex_unlock(&philo->data->forks[philo->left_fork->fork_id].fork);
        pthread_mutex_unlock(&philo->data->forks[philo->right_fork->fork_id].fork);
        philo->eating = 0;
        printf("%ld %d is sleeping\n", get_time(), philo->id);
        usleep(philo->data->time_to_sleep * 1000);
        printf("%ld %d is thinking\n", get_time(), philo->id);
    }
    return NULL;
}
