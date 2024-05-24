/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:14:51 by bjandri           #+#    #+#             */
/*   Updated: 2024/05/24 16:01:24 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(char *str, t_philo *philo)
{
	if (!philo_is_dead(philo))
	{
		pthread_mutex_lock(&philo->philo_mutex);
		printf("%ld %d %s\n", get_time() - philo->start_time, philo->id, str);
		pthread_mutex_unlock(&philo->philo_mutex);
	}
}

long	get_time(void)
{
	static struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_sleep(int time, t_philo *philo)
{
	int	start;

	start = get_time();
	while ((get_time() - start) < time
		&& philo_is_dead(philo) == 0)
		usleep(50);
}