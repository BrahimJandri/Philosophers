/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:01:50 by bjandri           #+#    #+#             */
/*   Updated: 2024/04/24 18:08:31 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
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
			sign *= -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
	{
		resu = resu * 10 + *s - '0';
		s++;
	}
	return (resu * sign);
}

int error_exit()
{
    printf("Error Argument Please Entr : [num_of_philo] [time_to_die] [time_to_eat] [time_to_sleep]\n");
    exit(1);
}

int check_int(int ac, char **av)
{
    int i;
    int j;
    
    i = 1;
    if(ac < 5 || ac > 6)
        error_exit();
    while(i < ac)
    {
        j = 0;
        while(av[i][j])
        {
            if((av[i][j] >= '0' && av[i][j] <= '9'))
                j++;
            else
                error_exit();
        }
        i++;
    }
    return (0);
}

void    init_args(char **str, t_philo *philo)
{   
    philo->num_of_philos = ft_atoi(str[1]);
    philo->time_to_die = ft_atoi(str[2]);
    philo->time_to_sleep = ft_atoi(str[3]);
    philo->num_times_to_eat = ft_atoi(str[4]);
}