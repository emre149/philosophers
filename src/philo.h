/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:29:05 by ededemog          #+#    #+#             */
/*   Updated: 2024/10/29 18:23:32 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/time.h>
#include <limits.h>

// STRUCTS

typedef struct s_philo
{
	int				id;
	int				nb_meals;
	bool			is_eating;
	pthread_t		thread;
	long int		last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t *right_fork;
	struct s_info 	*info;	
}	t_philo;

typedef struct s_info
{
	long int 		start;
	int				philo_nb;
	int				meal_needed;
	int				time2_die;
	int				time2_eat;
	int				time2_sleep;
	int				stop;
	t_philo			*philo;
	pthread_mutex_t	print;
	pthread_mutex_t	m_stop;
	pthread_mutex_t	m_eat;
	pthread_mutex_t dead;
}	t_info;

// UTILS

int		ft_atoi(char *str);
void	ft_usleep(int ms);
int		ft_isdigit(char c);


# endif