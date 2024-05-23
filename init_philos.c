/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:50:38 by bjandri           #+#    #+#             */
/*   Updated: 2024/05/23 16:18:19 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->philo_nb);
	if (!data->philos)
		error_input("malloc fails to allocate for philos");
	while (i < data->philo_nb)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = &data->fork_mutex[i];
		data->philos[i].right_fork = &data->fork_mutex[(i + 1) % data->philo_nb];
		data->philos[i].data = data;
		data->philos[i].last_meal = 0;
        data->philos->philo_deid = 0;
		data->philos[i].is_eating = 0;
		data->philos[i].number_of_meals = 0;
		i++;
	}
}
void	init_args(t_data *data, char **argv)
{
	data->philo_nb = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
    if(data->philo_nb > 200 || data->time_to_die < 60000 || data->time_to_eat < 60000 || data->time_to_sleep < 6000)
    {
        error_input("philos must be under 200 && time above 60ms");
    }
	if(argv[5])
    {
		data->philos->number_of_meals = ft_atol(argv[5]);
    }
	else
		data->philos->number_of_meals = -1;
	data->philos->philo_deid = 0;
}
