/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 09:10:40 by bjandri           #+#    #+#             */
/*   Updated: 2024/05/22 15:30:42 by bjandri          ###   ########.fr       */
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

long get_current_time(t_data *data)
{
    return (get_time() - data->dinner_start);
}

void check_death(void *arg)
{
    t_data *data;
    data = (t_data *)arg;
    int i = -1;
    while(++i < data->philo_nbr)
    {
        if (!data->philos[i].deid && get_current_time(data) - data->philos[i].last_meal > data->time_to_die)
        {
            data->philos[i].deid = true;
            data->end = true;
            printf("%ld %d died\n", get_current_time(data), data->philos[i].id);
            exit(EXIT_FAILURE);
        }
        // else if(data->philos->meals_counter == data->nb_limits_to_eat)
        //     exit(EXIT_FAILURE);
    }
}

void lock_mutex(t_philo *philo, int c)
{
    if(c == 1)
    {
        pthread_mutex_lock(philo->left_fork);
        pthread_mutex_lock(philo->right_fork);
    }
    else if(c == 0)
    {
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
    }
}

void ft_update(t_philo *philo)
{
    philo->eating = 1;
    philo->last_meal = get_current_time(philo->data);
    philo->meals_counter++;
}

void *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (!philo->data->end)
    {
        if (philo->id % 2 == 0)
            usleep(100);
        lock_mutex(philo, 1);
        printf("%ld %d is taken a fork\n", get_current_time(philo->data), philo->id);
        check_death(philo->data);
        printf("%ld %d is eating\n", get_current_time(philo->data), philo->id);
        ft_update(philo);
        usleep(philo->data->time_to_eat * 1000);
        lock_mutex(philo, 0);
        philo->eating = 0;
        check_death(philo->data);
        printf("%ld %d is sleeping\n", get_current_time(philo->data), philo->id);
        usleep(philo->data->time_to_sleep * 1000);
        check_death(philo->data);
        printf("%ld %d is thinking\n", get_current_time(philo->data), philo->id);
    }
    return NULL;
}

void print_msg(char *str, t_philo *philo)
{
    printf("%ld %d %s\n", get_current_time(philo->data), philo->id, str);
}