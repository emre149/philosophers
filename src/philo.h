/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:29:05 by ededemog          #+#    #+#             */
/*   Updated: 2024/12/02 08:33:14 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>

// STRUCTS

typedef struct s_philo
{
	int					id;
	int					nb_meals;
	bool				is_eating;
	pthread_t			thread;
	long long int		last_meal;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		left_fork;
	pthread_mutex_t		*right_fork;
	struct s_info		*info;	
}	t_philo;

typedef struct s_info
{
	long long int		start;
	int					philo_eat;
	int					philo_nb;
	int					meal_needed;
	int					time2_die;
	int					time2_eat;
	int					time2_sleep;
	int					stop;
	t_philo				*philo;
	pthread_mutex_t		print;
	pthread_mutex_t		m_stop;
	pthread_mutex_t		m_eat;
	pthread_mutex_t		dead;
}	t_info;

// CLEANING UTILS

void			destroy_global_mutex(t_info *info);
void			destroy_philo_mutex(t_info *info, int i);
int				cleanup(t_info	*info, int i, bool free_philo);

// INITS

int				parsing(int ac, char **av, t_info *info);
int				philo_init(t_info *info);

// PHILOS

bool			is_dead(t_philo *philo, int i);
void			*monitor_death(void *ph);
void			grab_fork(t_philo *philo);
void			eat(t_philo *philo);
void			*life(void	*p);

// UTILS

int				ft_atoi(char *str);
int				ft_isdigit(char c);
void			ft_usleep(int ms);
void			print(t_philo *philo, char *str);
void			free_all(t_info *info);
void			ft_fprintf(char *msg);
bool			safe_stop(t_info *info);
long long int	get_time(void);

#endif