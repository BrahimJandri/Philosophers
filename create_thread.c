/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 09:10:40 by bjandri           #+#    #+#             */
/*   Updated: 2024/05/17 15:29:00 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long get_timestamp_ms()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long long)(tv.tv_sec) * 1000 + (long long)(tv.tv_usec) / 1000;
}

void* philosopher_routine(void* arg)
{
    t_philo* philosopher = (t_philo*)arg;
    printf("Philosopher %d is executing\n", philosopher->id);
    return NULL;
}

void create_philos(int num_of_philos)
{
    int i = 1;
    t_philo philosophers[num_of_philos];
    while (i <= num_of_philos)
    {
        philosophers[i].id = i;
        pthread_create(&philosophers[i].thread, NULL, philosopher_routine, (void*)&philosophers[i]);
        i++;
    }
}