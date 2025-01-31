/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:48:05 by ededemog          #+#    #+#             */
/*   Updated: 2025/01/31 19:26:32 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static void	init_philos(t_philo *philo, t_main *main, int i)
{
	philo->main = main;
	philo->left_fork = &main->forks[i];
	philo->right_fork = &main->forks[(i + 1) % main->nb_philo];
	philo->id = i + 1;
	philo->meals_eaten = 0;
	philo->last_meal = 0;
}

static int	init_mutexes(t_main *main)
{
	int	i;

	if (pthread_mutex_init(&main->lock, NULL))
		return (1);
	i = 0;
	main->forks = malloc(sizeof(pthread_mutex_t) * main->nb_philo);
	if (!main->forks)
		return (1);
	while (i < main->nb_philo)
	{
		if (pthread_mutex_init(&main->forks[i], NULL))
		{
			while (i > 0)
				pthread_mutex_destroy(&main->forks[--i]);
			pthread_mutex_destroy(&main->lock);
			free(main->forks);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init(t_main *main)
{
	int	i;

	i = 0;
	main->philos_full = 0;
	main->stop = 0;
	main->start = 0;
	main->philos = malloc(sizeof(t_philo) * main->nb_philo);
	if (!main->philos)
	{
		printf("Error: Initialization array of philos structs failed\n");
		return (1);
	}
	if (init_mutexes(main))
	{
		free(main->philos);
		printf("Error: Initialization array of mutexes failed\n");
		return (1);
	}
	while (i < main->nb_philo)
	{
		init_philos(&main->philos[i], main, i);
		i++;
	}
	return (0);
}
