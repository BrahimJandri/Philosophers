/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:01:50 by bjandri           #+#    #+#             */
/*   Updated: 2024/05/15 16:43:30 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(char *str)
{
	int		sign;
	long	resu;
	char	*s;

	sign = 1;
	resu = 0;
	s = (char *)str;
	while ((*s >= 9 && *s <= 13) || *s == 32)
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			error_exit();
		else
			s++;
	}
	while (*s >= '0' && *s <= '9')
	{
		resu = resu * 10 + *s - '0';
		s++;
	}
	return (resu * sign);
}

int	error_exit(void)
{
	printf("Error Args Enter : ARG1 ==> [number_of_philo]\n");
	printf("ARG2 ==> [time_to_die]\n");
	printf("ARG3 ==> [time_to_eat]\n");
	printf("ARG4 ==> [time_to_sleep]\n");
	printf("ARG5 ==> Optional [number_of_meals]\n");
	exit(EXIT_FAILURE);
}

static void	check_num_philos(char *str)
{
	if (ft_atol(str) > 200)
	{
		printf("Philos Must Not Be More Than 200\n");
		exit(EXIT_FAILURE);
	}
}

int	check_int(int ac, char **av)
{
	int		i;
	int		j;
	long	tmp;

	i = 1;
	check_num_philos(av[1]);
	while (i < ac)
	{
		j = 0;
		tmp = ft_atol(av[i]);
		if (tmp > 2147483647 || tmp < -2147483648)
			error_exit();
		while (av[i][j] == '0' || av[i][j] == '+')
			j++;
		while (av[i][j])
		{
			if ((av[i][j] >= '0' && av[i][j] <= '9'))
				j++;
			else
				error_exit();
		}
		i++;
	}
	return (0);
}

void	init_args(char **str, t_philo *philo)
{
	philo->num_of_philos = ft_atol(str[1]);
	philo->time_to_die = ft_atol(str[2]);
	philo->time_to_sleep = ft_atol(str[3]);
	philo->num_times_to_eat = ft_atol(str[4]);
	philo->eaten_meals = ft_atol(str[5]);
	printf("philo->num_of_philos =====> %d\n", philo->num_of_philos);
	printf("philo->time_to_die =====> %ld\n", philo->time_to_die);
	printf("philo->time_to_sleep =====> %ld\n", philo->time_to_sleep);
	printf("philo->num_times_to_eat =====> %d\n", philo->num_times_to_eat);
	printf("philo->eaten_meals =====> %d\n", philo->eaten_meals);
}