/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 08:56:29 by bjandri           #+#    #+#             */
/*   Updated: 2024/05/18 10:22:39 by bjandri          ###   ########.fr       */
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



void    data_destroy(t_data *data)
{
    int i;

    i = -1;
    while (++i < data->philo_nbr)
        pthread_mutex_destroy(&data->forks[i].fork_id);
    free(data->philo_nbr);
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

void    *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (!philo->data->end)
    {
        pthread_mutex_lock(&philo->data->forks[philo->left_fork].fork_id);
        pthread_mutex_lock(&philo->data->forks[philo->right_fork].fork_id);
        philo->eating = 1;
        philo->last_meal = get_time();
        philo->meals_counter++;
        printf("%ld %d is eating\n", get_time(), philo->id);
        usleep(philo->data->time_to_eat * 1000);
        pthread_mutex_unlock(&philo->data->forks[philo->left_fork].fork_id);
        pthread_mutex_unlock(&philo->data->forks[philo->right_fork].fork_id);
        philo->eating = 0;
        printf("%ld %d is sleeping\n", get_time(), philo->id);
        usleep(philo->data->time_to_sleep * 1000);
        printf("%ld %d is thinking\n", get_time(), philo->id);
    }
    return (NULL);
}

long    get_time(void)
{
    struct timeval  tv;
    long            time;

    gettimeofday(&tv, NULL);
    time = tv.tv_sec * 1000;
    time += tv.tv_usec / 1000;
    return (time);
}

void    *safe_malloc(size_t size)
{
    void    *ptr;

    ptr = malloc(size);
    if (!ptr)
    {
        printf("Error: malloc failed\n");
        exit(1);
    }
    return (ptr);
}

int     main(int ac, char **av)
{
    t_data  data;

    if (ac != 5 && ac != 6)
        error_input("Error: wrong number of arguments\n");
    if (check_int(ac, av))
        error_input("Error: wrong argument\n");
    init_args(av, &data);
    data_init(&data);
    philo_init(&data);
    philo_create(&data);
    philo_join(&data);
    data_destroy(&data);
    philo_destroy(&data);
    return (0);
}

void    error_input(char *str)
{
    printf("%s", str);
    exit(1);
}

int     check_int(int ac, char **av)
{
    int i;
    int j;

    i = 1;
    while (i < ac)
    {
        j = 0;
        while (av[i][j])
        {
            if (av[i][j] < '0' || av[i][j] > '9')
                return (1);
            j++;
        }
        i++;
    }
    return (0);
}

void    init_args(char **str, t_data *data)
{
    data->philo_nbr = ft_atol(str[1]);
    data->time_to_die = ft_atol(str[2]);
    data->time_to_eat = ft_atol(str[3]);
    data->time_to_sleep = ft_atol(str[4]);
    if (str[5])
        data->nb_limits_to_eat = ft_atol(str[5]);
    else
        data->nb_limits_to_eat = -1;
}

long    ft_atol(char *str)
{
    long    res;
    int     i;

    res = 0;
    i = 0;
    while (str[i])
    {
        res = res * 10 + str[i] - '0';
        i++;
    }
    return (res);
}

