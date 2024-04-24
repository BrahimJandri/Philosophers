/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:08:58 by bjandri           #+#    #+#             */
/*   Updated: 2024/04/24 14:35:06 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int main(int ac, char **av)
{
    t_philo philo;

    (void)ac;
    
    philo.num_of_philos = ft_atoi(av[1]);
    philo.time_to_die = ft_atoi(av[2]);
    philo.time_to_sleep = ft_atoi(av[3]);
    philo.num_times_to_eat = ft_atoi(av[4]);

    printf("philo.num_of_philos = %d\n",  philo.num_of_philos);
    printf("philo.time_to_die = %ld\n",  philo.time_to_die);
    printf("philo.time_to_sleep = %ld\n",  philo.time_to_sleep);
    printf("philo.num_times_to_eat = %d\n",  philo.num_times_to_eat);
    
}
