/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:48:14 by ededemog          #+#    #+#             */
/*   Updated: 2025/01/31 19:25:16 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static int	philo_sleep(t_philo *philo)
{
	if (check_stop(philo))
		return (1);
	print(philo, "is sleeping", 0);
	if (philo_pause(philo->main->time_to_sleep, philo))
		return (1);
	return (0);
}

static void	lonely_philo(t_philo *philo)
{
	size_t	start_time;

	pthread_mutex_lock(philo->left_fork);
	start_time = philo->main->start_time;
	printf("%zu %d has taken a fork\n", get_current_time() - start_time, 1);
	philo_pause(philo->main->time_to_die, &philo->main->philos[0]);
	pthread_mutex_unlock(philo->left_fork);
}

static void	philo_wait(t_philo *philo)
{
	if (philo->id % 2)
	{
		print(philo, "is thinking", 0);
		philo_pause(1, philo);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->main->lock);
	while (!philo->main->start)
		usleep(1);
	pthread_mutex_unlock(&philo->main->lock);
	if (philo->main->nb_philo == 1)
	{
		lonely_philo(philo);
		return (philo);
	}
	philo_wait(philo);
	while (!check_stop(philo))
	{
		if (eat(philo))
			break ;
		if (philo_sleep(philo))
			break ;
		if (!check_stop(philo))
			print(philo, "is thinking", 0);
		else
			break ;
	}
	return (philo);
}
