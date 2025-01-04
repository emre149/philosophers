/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:22:59 by ededemog          #+#    #+#             */
/*   Updated: 2025/01/04 19:04:13 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_death(void *ph)
{
	t_philo		*philo;
	long long	last_meal_time;
	bool		should_continue;

	philo = (t_philo *)ph;
	while (1)
	{
		usleep(50);
		pthread_mutex_lock(&philo->info->m_stop);
		should_continue = !philo->info->stop;
		pthread_mutex_unlock(&philo->info->m_stop);

		if (!should_continue)
			return (NULL);

		pthread_mutex_lock(&philo->meal_lock);
		last_meal_time = philo->last_meal;
		if (!philo->is_eating && (get_time() - last_meal_time > philo->info->time2_die))
		{
			pthread_mutex_lock(&philo->info->m_stop);
			if (!philo->info->stop)
			{
				philo->info->stop = true;
				pthread_mutex_lock(&philo->info->print);
				printf("%lld %d died\n", get_time() - philo->info->start, philo->id);
				pthread_mutex_unlock(&philo->info->print);
			}
			pthread_mutex_unlock(&philo->info->m_stop);
			pthread_mutex_unlock(&philo->meal_lock);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->meal_lock);
	}
}

// static void	lonely_philo(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->left_fork);
// 	print(philo, " has taken a fork\n");
// 	ft_usleep(philo->info->time2_die);
// 	pthread_mutex_lock(&philo->info->m_stop);
// 	if (!philo->info->stop)
// 	{
// 		philo->info->stop = true;
// 		pthread_mutex_lock(&philo->info->print);
// 		printf("%lld %d died\n", get_time() - philo->info->start, philo->id);
// 		pthread_mutex_unlock(&philo->info->print);
// 	}
// 	pthread_mutex_unlock(&philo->info->m_stop);
// 	pthread_mutex_unlock(&philo->left_fork);
// }

// void	grab_fork(t_philo *philo)
// {
// 	if (philo->info->philo_nb == 1)
// 	{
// 		lonely_philo(philo);
// 		return ;
// 	}
// 	if (philo->id % 2 == 0)
// 	{
// 		pthread_mutex_lock(&philo->left_fork);
// 		print(philo, " has taken a fork\n");
// 		pthread_mutex_lock(philo->right_fork);
// 		print(philo, " has taken a fork\n");
// 	}
// 	else
// 	{
// 		usleep(500);
// 		pthread_mutex_lock(philo->right_fork);
// 		print(philo, " has taken a fork\n");
// 		pthread_mutex_lock(&philo->left_fork);
// 		print(philo, " has taken a fork\n");
// 	}
// }

void	grab_fork(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->id % 2 == 0)
	{
		first_fork = &philo->left_fork;
		second_fork = philo->right_fork;
	}
	else
	{
		usleep(500);
		first_fork = philo->right_fork;
		second_fork = &philo->left_fork;
	}
	pthread_mutex_lock(first_fork);
	print(philo, " has taken a fork\n");
	pthread_mutex_lock(second_fork);
	print(philo, " has taken a fork\n");
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
		ft_usleep(10);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_lock);
	if (pthread_create(&t, NULL, monitor_death, philo) != 0)
		return (NULL);
	pthread_detach(t);
	while (!is_dead(philo, 0))
	{
		grab_fork(philo);
		pthread_mutex_lock(&philo->meal_lock);
		philo->is_eating = true;
		pthread_mutex_unlock(&philo->meal_lock);
		eat(philo);
		pthread_mutex_lock(&philo->meal_lock);
		philo->is_eating = false;
		if (philo->nb_meals == philo->info->meal_needed)
		{
			pthread_mutex_unlock(&philo->meal_lock);
			pthread_mutex_lock(&philo->info->m_philo_eat);
			if (++philo->info->philo_eat == philo->info->philo_nb)
			{
				pthread_mutex_lock(&philo->info->m_stop);
				philo->info->stop = true;
				pthread_mutex_unlock(&philo->info->m_stop);
				pthread_mutex_lock(&philo->info->print);
				printf("All philosophers have eaten %d times\n", 
					philo->info->meal_needed);
				pthread_mutex_unlock(&philo->info->print);
			}
			pthread_mutex_unlock(&philo->info->m_philo_eat);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->meal_lock);
	}
	return (NULL);
}
