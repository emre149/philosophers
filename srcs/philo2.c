/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:00:26 by ededemog          #+#    #+#             */
/*   Updated: 2025/01/31 19:26:39 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static void	filled_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->main->lock);
	if (philo->main->nb_meals == philo->meals_eaten)
		philo->main->philos_full += 1;
	pthread_mutex_unlock(&philo->main->lock);
}

static int	grab_fork(t_philo *philo)
{
	if (check_stop(philo))
		return (1);
	pthread_mutex_lock(philo->left_fork);
	print(philo, "has taken a fork", 0);
	pthread_mutex_lock(philo->right_fork);
	print(philo, "has taken a fork", 0);
	if (check_stop(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	return (0);
}

int	eat(t_philo *philo)
{
	if (check_stop(philo))
		return (1);
	if (grab_fork(philo))
		return (1);
	print(philo, "is eating", 0);
	pthread_mutex_lock(&philo->main->lock);
	philo->last_meal = get_current_time() - philo->main->start_time;
	pthread_mutex_unlock(&philo->main->lock);
	if (philo_pause(philo->main->time_to_eat, philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	philo->meals_eaten += 1;
	filled_check(philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}
