/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:03:04 by bjandri           #+#    #+#             */
/*   Updated: 2024/05/23 12:10:00 by bjandri          ###   ########.fr       */
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
	int				philo_deid;
	long			last_meal;
	int				meals_counter;
	int				eating;
	long			start_time;
	pthread_mutex_t			philo_mutex;
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
	t_fork					*forks;
	t_philo					*philos;
}				t_data;


// check_args

long				ft_atol(char *str);
void 				error_input(char *str);
int					check_int(int ac, char **av);
void				init_args(char **str, t_data *data);


// philo_ation

int					philo_takes_forks(t_philo *philo);
void				philo_is_eating(t_philo *philo);
int 				philo_is_dead(t_philo *philo);
void				philo_is_sleeping(t_philo *philo);
void				philo_is_thinking(t_philo *philo);

// philos_routine

void    			*philo_routine(void *arg);
void				join_threads(t_data *data);
void				begin_philosophers_routine(t_data *data);


// philo_monitoring

int					check_last_meal(t_philo *philo);
int					check_if_one_is_dead(t_data *data);
void				free_philo(t_data *data);
void				*start_monitoring(void *arg);

// utils.c

long				get_time(void);
void				print_msg(char *str, t_philo *philo);
void				ft_sleep(int time, t_philo *philo);

#endif