/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:03:04 by bjandri           #+#    #+#             */
/*   Updated: 2024/06/06 12:07:38 by bjandri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define BLUE "\e[1;34m"

typedef struct s_philo
{
	int				id;
	int				is_full;
	long			last_meal;
	int				meals_counter;
	long			start_time;
	struct s_data	*data;
	pthread_t		thread_id;
	pthread_t		thread_die;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}					t_philo;

typedef struct s_data
{
	int				is_full;
	int				die;
	int				philo_nb;
	long			time_to_die;
	long			time_to_sleep;
	long			time_to_eat;
	int				number_of_meals;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	print_mutex;
	pthread_t		moni;
	t_philo			*philos;

}					t_data;

void				free_all(t_data *data);

// parsing.c

int					ft_strlen(char *str);
int					error_input(char *str);
void				thread_fail(char *str);
long				ft_atol(char *str);
int					check_int(int ac, char **av);

// init_philos.c

int					init_philo_args(t_data *data, char **av);
int					create_philos(t_data *data);
int					create_forks(t_data *data);
int					init_philos(t_data *data);

// utils.c

int					check_is_full(t_data *data);
int					check_if_dead(t_philo *philo);
void				*monitoring(void *arg);
int					check_full_die(t_data *data);

// philo_routine.c

void				taking_forks(t_philo *philo);
void				print_status(char *str, t_philo *philo);
void				is_eating(t_philo *philo);
void				sleep_think(t_philo *philo);
void				*philo_routine(void *arg);

// time.c

void				ft_sleep(long time);
long				get_time(void);

#endif