/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:03:04 by bjandri           #+#    #+#             */
/*   Updated: 2024/05/21 10:58:27 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_data t_data;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int	fork_id;
}				t_fork;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	bool			full;
	long			last_meal;
	int				meals_counter;
	int				eating;
	long			start_time;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
	t_data			*data;
}					t_philo;

typedef struct s_data
{
	long 					philo_nbr;
	long					time_to_die;
	long					time_to_eat;
	long					time_to_sleep;
	long					nb_limits_to_eat;
	long					dinner_start;
	bool					end;
	pthread_mutex_t			data_mutex;
	t_fork					*forks;
	t_philo					*philos;
}				t_data;

long				ft_atol(char *str);
int					check_int(int ac, char **av);
void				init_args(char **str, t_data *data);
void 				error_input(char *str);
void    			*philo_routine(void *arg);
void   				philo_join(t_data *data);
void    			philo_create(t_data *data);
void    			philo_destroy(t_data *data);
void    			philo_init(t_data *data);
void    			data_destroy(t_data *data);
void    			data_init(t_data *data);
long    			get_time(void);
#endif