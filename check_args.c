/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:01:50 by bjandri           #+#    #+#             */
/*   Updated: 2024/05/23 12:37:14 by bjandri          ###   ########.fr       */
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
			error_input("number can not be negative");
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
void error_input(char *str)
{
	printf("%s\n", str);
	exit(EXIT_FAILURE);
}


int	check_int(int ac, char **av)
{
	int		i;
	int		j;
	long	tmp;

	i = 1;
	while (i < ac)
	{
		j = 0;
		tmp = ft_atol(av[i]);
		if (tmp > 2147483647 || tmp < -2147483648)
			error_input("Number Can Not Be More Or Less Than MIN MAX INT");
		while (av[i][j] == '0' || av[i][j] == '+')
			j++;
		while (av[i][j])
		{
			if ((av[i][j] >= '0' && av[i][j] <= '9'))
				j++;
			else
				error_input("Please Entre a Valid Number");
		}
		i++;
	}
	return (0);
}

void	init_args(char **str, t_data *data)
{
	data->philo_nb = ft_atol(str[1]);
	data->time_to_die = ft_atol(str[2]);
	data->time_to_eat = ft_atol(str[3]);
	data->time_to_sleep = ft_atol(str[4]);
	if(data->philo_nb > 200 || data->time_to_die < 0 || data->time_to_eat < 0 || data->time_to_sleep < 0)
		error_input("use less than 200 philos and more than 60ms in the rest of args");
	if(str[5])
		data->number_of_meals = ft_atol(str[5]);
	else
	data->number_of_meals = -1;
}
