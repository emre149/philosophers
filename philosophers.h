/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:47:54 by ededemog          #+#    #+#             */
/*   Updated: 2025/01/31 19:25:42 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_main	t_main;

typedef struct s_philo
{
	t_main				*main;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	size_t				last_meal;
	int					meals_eaten;
	int					id;
}						t_philo;

typedef struct s_main
{
	int					nb_philo;
	t_philo				*philos;
	pthread_mutex_t		lock;
	pthread_mutex_t		*forks;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				start_time;
	int					philos_full;
	int					nb_meals;
	int					stop;
	int					start;
}						t_main;

// parser
int						parser(t_main *main, char **str, int ac);

// utils
size_t					get_current_time(void);
void					print(t_philo *philo, char *str, int flag);
int						philo_pause(size_t ms, t_philo *philo);
int						check_stop(t_philo *philo);

// init
int						init(t_main *main);

// clean
void					clean(t_main *main);
void					join_threads(t_main *main, int i);

// simu
int						start(t_main *main);
void					monitor(t_main *main);

// philo
void					*routine(void *arg);
int						eat(t_philo *philo);

#endif