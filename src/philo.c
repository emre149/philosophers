/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:22:59 by ededemog          #+#    #+#             */
/*   Updated: 2024/11/25 11:26:05 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_death(void *ph)
{
	t_philo	*philo = (t_philo *)ph;
	ft_usleep(philo->info->time2_die + 1);

	pthread_mutex_lock(&philo->info->m_eat);
	pthread_mutex_lock(&philo->info->m_stop);
	pthread_mutex_lock(&philo->meal_lock);

	if (!philo->is_eating && (get_time() - philo->last_meal >= philo->info->time2_die))
	{
		pthread_mutex_unlock(&philo->meal_lock);
		pthread_mutex_unlock(&philo->info->m_eat);
		pthread_mutex_unlock(&philo->info->m_stop);
		print(philo, " died\n");
		is_dead(philo, true);
	}
	else
	{
		pthread_mutex_unlock(&philo->meal_lock);
		pthread_mutex_unlock(&philo->info->m_eat);
		pthread_mutex_unlock(&philo->info->m_stop);
	}
	return (NULL);
}

void	grab_fork(t_philo *philo)
{
	if (philo->info->philo_nb == 1)
	{
		ft_usleep(philo->info->time2_die);
		pthread_mutex_unlock(&philo->left_fork);
		return ;
	}
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print(philo, " has taken a fork\n");
		pthread_mutex_lock(&philo->left_fork);
		print(philo, " has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork);
		print(philo, " has taken a fork\n");
		pthread_mutex_lock(philo->right_fork);
		print(philo, " has taken a fork\n");
	}
}

void	eat(t_philo *philo)
{
	print(philo, " is eating\n");
	pthread_mutex_lock(&philo->info->m_eat);
	philo->last_meal = get_time();
	pthread_mutex_lock(&philo->meal_lock);
	philo->nb_meals++;
	pthread_mutex_unlock(&philo->meal_lock);
	pthread_mutex_unlock(&philo->info->m_eat);

	ft_usleep(philo->info->time2_eat);

	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);

	print(philo, " is sleeping\n");
	ft_usleep(philo->info->time2_sleep);

	print(philo, " is thinking\n");
}

void	*life(void	*p)
{
	t_philo 	*philo;
	pthread_t 	t;

	philo = (t_philo *)p;

	if (philo->id % 2 == 0)
		ft_usleep(philo->info->time2_die / 10);
	while (!is_dead(philo, 0))
	{
		pthread_mutex_lock(&philo->info->m_stop);
		if (philo->info->stop)
		{
			pthread_mutex_unlock(&philo->info->m_stop);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->info->m_stop);
		pthread_create(&t, NULL, monitor_death, philo);
		grab_fork(philo);
		eat(philo);
		pthread_detach(t);
		if (philo->nb_meals == philo->info->meal_needed)
		{
			pthread_mutex_unlock(&philo->meal_lock);
			pthread_mutex_lock(&philo->info->m_stop);
			if (++philo->info->philo_eat == philo->info->philo_nb)
			{
                pthread_mutex_unlock(&philo->info->m_stop);
                is_dead(philo, false);
				philo->info->stop = true;
			}
			else
				pthread_mutex_unlock(&philo->info->m_stop);
			return (NULL);
		}
	}
	return (NULL);
}