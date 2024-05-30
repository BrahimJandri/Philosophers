/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjandri <bjandri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:03:04 by bjandri           #+#    #+#             */
/*   Updated: 2024/05/30 18:26:07 by bjandri          ###   ########.fr       */
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
	int				die;
	int				philo_nb;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				number_of_meals;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	print_mutex;
	t_philo			*philos;

}					t_data;

// parsing.c

int					ft_strlen(char *str);
void				error_input(char *str);
long				ft_atol(char *str);
int					check_int(int ac, char **av);

// init_philos.c

void				init_philo_args(t_data *data, char **av);
void				create_philos(t_data *data);
void				create_forks(t_data *data);
void				init_philos(t_data *data, char **av);
int					check_is_full(t_philo *philo);


// utils.c

long				get_time(void);
long				get_current_time(t_data *data);

// philo_routine.c

void				*philo_routine(void *arg);
int					check_if_dead(t_philo *philo);
void				taking_forks(t_philo *philo);
void				is_eating(t_philo *philo);
void				sleep_think(t_philo *philo);
void				print_status(char *str, t_philo *philo);

// for usleep
void				ft_sleep(int time);
void 				*monitoring(void *arg);

#endif