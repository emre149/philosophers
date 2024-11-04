/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:19:10 by ededemog          #+#    #+#             */
/*   Updated: 2024/11/04 15:11:27 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parsing(int ac, char **av, t_info *info)
{
	if (ac != 5 && ac != 6)
	{
		printf("Arguments Error: number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	info->philo_nb = ft_atoi(av[1]);
	if (info->philo_nb <= 0) return (0);
	info->time2_die = ft_atoi(av[2]);
	if (info->time2_die <= 0) return (0);
	info->time2_eat = ft_atoi(av[3]);
	if (info->time2_eat <= 0) return (0);
	info->time2_sleep = ft_atoi(av[4]);
	if (info->time2_sleep <= 0) return (0);
	info->meal_needed = (ac == 6) ? ft_atoi(av[5]) : -1;
	if (ac == 6 && info->meal_needed <= 0) return (0);
	info->stop = false;

	return (1);
}

int	philo_init(t_info *info)
{
	int	i;

	i = 0;
	info->philo = malloc(sizeof(t_philo) * info->philo_nb);
	if (!info->philo)
		return (0);
	
	if (pthread_mutex_init(&info->m_stop, NULL) != 0 ||
		pthread_mutex_init(&info->m_eat, NULL) != 0 ||
		pthread_mutex_init(&info->dead, NULL) != 0)
	{
		free_all(info);
		return (0);
	}

	while (i < info->philo_nb)
	{
		info->philo[i].id = i + 1;
		info->philo[i].nb_meals = 0;
		info->philo[i].is_eating = false;
		info->philo[i].last_meal = info->start;
		info->philo[i].info = info;

		if (pthread_mutex_init(&info->philo[i].left_fork, NULL) != 0 \
		|| pthread_mutex_init(&info->philo[i].meal_lock, NULL) != 0)
		{
			free_all(info);
			return (cleanup(info, i, true));
		}
		if (i == 0)
			info->philo[i].right_fork = &info->philo[info->philo_nb - 1].left_fork;
		else
			info->philo[i].right_fork = &info->philo[i - 1].left_fork;
		i++;
	}
	return (1);
}