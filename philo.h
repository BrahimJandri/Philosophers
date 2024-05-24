/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:03:04 by bjandri           #+#    #+#             */
/*   Updated: 2024/05/24 16:03:32 by bjandri          ###   ########.fr       */
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


typedef struct s_philo
{
	int					id;
	int					last_meal;
	int					is_eating;
	int					meals_counter;
	int					start_time;
	int					philo_deid;
	struct s_data		*data;
	pthread_mutex_t		philo_mutex;
	pthread_t			thread_id;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
}	t_philo;

typedef struct s_data
{
	int					philo_nb;
	int					time_to_die;
	int					time_to_sleep;
	int					time_to_eat;
	int					number_of_meals;
	pthread_mutex_t		*fork_mutex;
	t_philo				*philos;
}	t_data;


// init_philos.c

void				init_philo(t_data *data);
void				forks_creat(t_data *data);
void				init_args(t_data *data, char **argv);


// check_args

long				ft_atol(char *str);
void 				error_input(char *str);
int					check_int(int ac, char **av);

// philo_action

int					philo_takes_forks(t_philo *philo);
void				philo_is_eating(t_philo *philo);
int 				philo_is_dead(t_philo *philo);
void				philo_is_sleeping(t_philo *philo);
void				philo_is_thinking(t_philo *philo);

// philos_routine

void    			*philo_routine(void *arg);
void				start_philo_routine(t_philo *philo);

// philo_monitoring

int					check_last_meal(t_philo *philo);
int					check_if_one_is_dead(t_data *data);
void				free_philo(t_data *data);
void				*start_monitoring(void *arg);

// utils.c

long				get_time(void);
long				get_curr_time(t_philo *philo);
void				print_msg(char *str, t_philo *philo);
void				ft_sleep(int time, t_philo *philo);

#endif