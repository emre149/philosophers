/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:22:59 by ededemog          #+#    #+#             */
/*   Updated: 2024/12/02 12:17:38 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_death(void *ph)
{
	t_philo		*philo;
	bool		is_eating_state;
	long long	last_meal_time;

	philo = (t_philo *)ph;
	while (1)
	{
		pthread_mutex_lock(&philo->meal_lock);
		is_eating_state = philo->is_eating;
		last_meal_time = philo->last_meal;
		pthread_mutex_unlock(&philo->meal_lock);
		if (is_dead(philo, 0))
			return (NULL);
		if (!is_eating_state && (get_time() - last_meal_time >= \
		philo->info->time2_die))
		{
			pthread_mutex_lock(&philo->info->m_stop);
			if (!philo->info->stop)
			{
				philo->info->stop = true;
				pthread_mutex_lock(&philo->info->print);
				printf("%lld %d died\n", get_time() - philo->info->start, \
				philo->id);
				pthread_mutex_unlock(&philo->info->print);
			}
			pthread_mutex_unlock(&philo->info->m_stop);
			return (NULL);
		}
		ft_usleep(1);
	}
	return (NULL);
}

static void	lonely_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	print(philo, " has taken a fork\n");
	ft_usleep(philo->info->time2_die);
	print(philo, " died\n");
	pthread_mutex_lock(&philo->info->m_stop);
	philo->info->stop = true;
	pthread_mutex_unlock(&philo->info->m_stop);
	pthread_mutex_unlock(&philo->left_fork);
}

void	grab_fork(t_philo *philo)
{
	if (philo->info->philo_nb == 1)
	{
		lonely_philo(philo);
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
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_time();
	philo->nb_meals++;
	pthread_mutex_unlock(&philo->meal_lock);
	ft_usleep(philo->info->time2_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
	print(philo, " is sleeping\n");
	ft_usleep(philo->info->time2_sleep);
	print(philo, " is thinking\n");
}

void	*life(void	*p)
{
	t_philo		*philo;
	pthread_t	t;

	philo = (t_philo *)p;
	if (philo->id % 2 == 0)
		ft_usleep(philo->info->time2_die / 10);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_lock);
	if (pthread_create(&t, NULL, monitor_death, philo) != 0)
		return (NULL);
	pthread_detach(t);
	while (!is_dead(philo, 0))
	{
		grab_fork(philo);
		pthread_mutex_lock(&philo->info->m_stop);
		if (philo->info->stop)
		{
			pthread_mutex_unlock(&philo->info->m_stop);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->info->m_stop);
		pthread_mutex_lock(&philo->meal_lock);
		philo->is_eating = true;
		philo->last_meal = get_time();
		pthread_mutex_unlock(&philo->meal_lock);
		eat(philo);
		pthread_mutex_lock(&philo->meal_lock);
		philo->is_eating = false;
		if (philo->nb_meals == philo->info->meal_needed)
		{
			pthread_mutex_unlock(&philo->meal_lock);
			pthread_mutex_lock(&philo->info->m_stop);
			if (++philo->info->philo_eat == philo->info->philo_nb)
			{
				is_dead(philo, 1);
				pthread_mutex_unlock(&philo->info->m_stop);
				return (NULL);
			}
			pthread_mutex_unlock(&philo->info->m_stop);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->meal_lock);
	}
	return (NULL);
}
