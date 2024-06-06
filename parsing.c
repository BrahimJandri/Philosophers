/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:35:21 by bjandri           #+#    #+#             */
/*   Updated: 2024/06/06 12:11:29 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	error_input(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}

void	thread_fail(char *str)
{
	error_input(str);
	return ;
}

long	ft_atol(char *str)
{
	int		sign;
	long	res;
	char	*s;

	sign = 1;
	res = 0;
	s = (char *)str;
	while ((*s >= 9 && *s <= 13) || *s == 32)
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			error_input("Number can't be Negative ❌\n");
		else
			s++;
	}
	while (*s >= '0' && *s <= '9')
	{
		res = res * 10 + *s - '0';
		s++;
	}
	return (res * sign);
}

int	check_int(int ac, char **av)
{
	int		i;
	long	tmp;
	int		j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		tmp = ft_atol(av[i]);
		if (tmp > INT_MAX || tmp < INT_MIN)
			return (error_input("Number can't be greater than \
int max or less than int min ❌\n"), 1);
		while (av[i][j] == '0' || av[i][j] == '+' || av[i][j] == ' ')
			j++;
		while (av[i][j])
		{
			if ((av[i][j] >= '0' && av[i][j] <= '9'))
				j++;
			else
				return (error_input("Please enter a valid number\n"), 1);
		}
		i++;
	}
	return (0);
}
