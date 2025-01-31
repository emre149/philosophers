/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:48:19 by ededemog          #+#    #+#             */
/*   Updated: 2025/01/31 19:25:22 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static int	hungry_check(t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->main->lock);
	if (philo->main->stop != 1)
	{
		time = get_current_time() - philo->main->start_time;
		if (time - philo->last_meal > philo->main->time_to_die)
		{
			pthread_mutex_unlock(&philo->main->lock);
			print(philo, "died", 1);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->main->lock);
	return (0);
}

static int	philos_check(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->nb_philo)
	{
		if (hungry_check(&main->philos[i++]))
			return (1);
	}
	return (0);
}

static int	conditions_check(t_main *main)
{
	int	meals_eaten;
	int	nb_philos;

	if (philos_check(main))
		return (1);
	pthread_mutex_lock(&main->lock);
	meals_eaten = main->philos_full;
	nb_philos = main->nb_philo;
	pthread_mutex_unlock(&main->lock);
	if (meals_eaten == nb_philos)
	{
		pthread_mutex_lock(&main->lock);
		main->stop = 1;
		pthread_mutex_unlock(&main->lock);
		return (1);
	}
	return (0);
}

void	monitor(t_main *main)
{
	while (1)
	{
		if (conditions_check(main))
			break ;
	}
	join_threads(main, main->nb_philo);
	clean(main);
}

int	start(t_main *main)
{
	int	i;
	int	error;

	i = 0;
	pthread_mutex_lock(&main->lock);
	while (i < main->nb_philo)
	{
		error = pthread_create(&main->philos[i].thread, NULL, &routine,
				(void *)&main->philos[i]);
		if (error)
		{
			main->stop = 1;
			pthread_mutex_unlock(&main->lock);
			join_threads(main, i);
			clean(main);
			printf("Error: Thread creation failed\n");
			return (1);
		}
		i++;
	}
	main->start_time = get_current_time();
	main->start = 1;
	pthread_mutex_unlock(&main->lock);
	return (0);
}
