/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:19:10 by ededemog          #+#    #+#             */
/*   Updated: 2024/11/04 12:00:08 by ededemog         ###   ########.fr       */
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
	info->time2_die = ft_atoi(av[2]);
	info->time2_eat = ft_atoi(av[3]);
	info->time2_sleep = ft_atoi(av[4]);
	info->meal_needed = (ac == 6) ? ft_atoi(av[5]) : -1;
	info->stop = false;

	if (info->philo_nb <= 0 || info->time2_die <= 0 || info->time2_eat <= 0 || info->time2_sleep <= 0 || (ac == 6 && info->meal_needed <= 0))
	{
		printf("Arguments Error: arguments must be positive integers\n");
		return (0);
	}
	
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
		free(info->philo);
		destroy_global_mutex(info);
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
			return (cleanup(info, i, true));
		if (i == 0)
			info->philo[i].right_fork = &info->philo[info->philo_nb - 1].left_fork;
		else
			info->philo[i].right_fork = &info->philo[i - 1].left_fork;
		i++;
	}
	return (1);
}

void	*philo_routine(void *av)
{
	t_philo	*philo = (t_philo *)av;
	long	thinking_time;

	if (philo->info->philo_nb == 1)
	{
		print(philo, "has taken a fork\n");
		ft_usleep(philo->info->time2_die);
		return (NULL);
	}
	if (philo->id % 2)
		ft_usleep(philo->info->time2_eat);
	while (!safe_stop(philo->info))
	{
		print(philo, "is thinking\n");
		thinking_time = (philo->info->time2_die 
							- (get_time() - philo->last_meal) 
							- philo->info->time2_eat) / 2;
		if (thinking_time > 0)
			ft_usleep(thinking_time);
		
		pthread_mutex_lock(philo->left_fork);
		print(philo, "has taken a fork\n");
		pthread_mutex_lock(philo->right_fork);
		print(philo, "has taken a fork\n");

		print(philo, "is eating\n");
		pthread_mutex_lock(&philo->meal_lock);
		philo->is_eating = true;
		philo->last_meal = get_time();
		pthread_mutex_unlock(&philo->meal_lock);
		
		ft_usleep(philo->info->time2_eat);
		
		pthread_mutex_lock(&philo->meal_lock);
		philo->nb_meals++;
		philo->is_eating = false;
		pthread_mutex_unlock(&philo->meal_lock);

		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);

		print(philo, "is sleeping\n");
		ft_usleep(philo->info->time2_sleep);
	}
	return (NULL);
}


int	philo_thread(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->philo_nb)
	{
		if (pthread_create(&info->philo[i].thread, NULL, philo_routine, &info->philo[i]))
		{
			while (--i >= 0)
				pthread_detach(info->philo[i].thread);
			return (cleanup(info, info->philo_nb - 1, true));
		}
		i++;
	}
	i = 0;
	while (i < info->philo_nb)
	{
		if (pthread_join(info->philo[i].thread, NULL))
			return (cleanup(info, info->philo_nb - 1, true));
		i++;
	}
	return (1);
}