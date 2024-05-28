/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:04:36 by bjandri           #+#    #+#             */
/*   Updated: 2024/05/28 18:27:08 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_philo_args(t_data *data, char **av)
{
    data->philo_nb = ft_atol(av[1]);
    data->time_to_die = ft_atol(av[2]);
    data->time_to_eat = ft_atol(av[3]) * 1000;
    data->time_to_sleep = ft_atol(av[4]) * 1000;
    if (av[5])
    {
        data->number_of_meals = ft_atol(av[5]);
    }
    else
        data->number_of_meals = -1;
    if(data->number_of_meals == 0 || data->philo_nb == 0)
    {
        printf("ERROR : philo and number of meals must be more than 0\n");
        return; 
    }
}

void create_philos(t_data *data)
{
    int i = 0;
    data->philos->start_time = get_time();
    while (i < data->philo_nb)
    {
        if (pthread_create(&data->philos[i].thread_id, NULL, philo_routine,
                (void *)&data->philos[i]) != 0)
        {
            error_input("pthread_create failed\n");
            return;
        }
        i++;
    }
    i = 0;
    while (i < data->philo_nb) {
        if (pthread_join(data->philos[i].thread_id, NULL) != 0) {
            error_input("pthread_join failed\n");
            return;
        }
        i++;
    }
}

void create_forks(t_data *data)
{
    int i;
    
    i = 0;
    data->fork_mutex = malloc(sizeof(pthread_mutex_t) * data->philo_nb);
    if (!data->fork_mutex)
        error_input("malloc forks fails\n");
    pthread_mutex_init(&data->print_mutex, NULL);
    while (i < data->philo_nb)
    {
        if(pthread_mutex_init(&data->fork_mutex[i], NULL) != 0)
        {
            error_input("pthread_mutex_init failed\n");
            return ;
        }
        i++;
    }
}

void init_philos(t_data *data, char **av)
{
    int i;

    init_philo_args(data, av);
    create_forks(data);
    pthread_mutex_init(&data->lock_mutex, NULL);
    pthread_mutex_init(&data->print_mutex, NULL);
    data->philos = malloc(sizeof(t_philo) * data->philo_nb);
    if (!data->philos)
        error_input("malloc philo fails\n");
    i = 0;
    data->philos->die = 0;
    while (i < data->philo_nb)
    {
        data->philos[i].id = i + 1;
        data->philos[i].left_fork = &data->fork_mutex[i];
        data->philos[i].right_fork = &data->fork_mutex[(i + 1)
            % data->philo_nb];
        data->philos[i].last_meal = get_time();
        data->philos[i].meals_counter = 0;
        data->philos[i].data = data;
        i++;
    }
    create_philos(data);
}

int check_is_full(t_philo *philo)
{
    usleep(100);
    if (philo->data->number_of_meals == philo->meals_counter)
    {
        pthread_mutex_lock(&philo->data->print_mutex);
        printf("Every Philosopher had %d meals!\n", philo->data->number_of_meals);
        pthread_mutex_unlock(&philo->data->print_mutex);
        return (1);
    }
    return (0);
}