/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:24:43 by bjandri           #+#    #+#             */
/*   Updated: 2024/05/25 17:08:10 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    if (philo->id % 2 == 0)
        usleep(1000);
    while (1)
    {
        // pthread_mutex_lock(&philo->data->print_mutex);
        // if (philo->data->philo_deid != 0)
        // {
        //     pthread_mutex_unlock(&philo->data->print_mutex);
        //     break;
        // }
        pthread_mutex_unlock(&philo->data->print_mutex);
        if (philo->id % 2 == 0)
        {
            pthread_mutex_lock(philo->right_fork);
            printf("%ld %d has taking a fork\n", get_current_time(philo->data), philo->id);
            pthread_mutex_lock(philo->left_fork);
            printf("%ld %d has taking a fork\n", get_current_time(philo->data), philo->id);     
        }
        else
        {
            pthread_mutex_lock(philo->left_fork);
            printf("%ld %d has taking a fork\n", get_current_time(philo->data), philo->id);
            pthread_mutex_lock(philo->right_fork);
            printf("%ld %d has taking a fork\n", get_current_time(philo->data), philo->id);            
        }

        printf("%ld %d is eating\n", get_current_time(philo->data), philo->id);
        philo->last_meal = get_time();
        usleep(20000);
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        printf("%ld %d is sleeping\n", get_current_time(philo->data), philo->id);
        usleep(20000);
        printf("%ld %d is thinking\n", get_current_time(philo->data), philo->id);
    }
    return NULL;
}

int check_if_dead(t_philo *philo)
{
    usleep(100);
    if (get_time() - philo->last_meal > philo->data->time_to_die)
    {
        pthread_mutex_lock(&philo->data->print_mutex);
        philo->data->philo_deid = 1;
        pthread_mutex_unlock(&philo->data->print_mutex);
        
        pthread_mutex_lock(&philo->data->print_mutex);
        printf("%ld %d has died\n", get_current_time(philo->data), philo->id);
        pthread_mutex_unlock(&philo->data->print_mutex);
        return 1;
    }
    return 0;
}
