/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:22:59 by ededemog          #+#    #+#             */
/*   Updated: 2024/11/04 19:11:30 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_death(void *ph)
{
	t_philo	*philo = (t_philo *)ph;
	ft_usleep(philo->info->time2_die + 1);

	pthread_mutex_lock(&philo->info->m_eat);
	pthread_mutex_lock(&philo->info->m_stop);

	if (!philo->is_eating && (get_time() - philo->last_meal >= philo->info->time2_die))
	{
		pthread_mutex_unlock(&philo->info->m_eat);
		pthread_mutex_unlock(&philo->info->m_stop);
		print(philo, " died\n");
		is_dead(philo, true);
	}
	pthread_mutex_unlock(&philo->info->m_eat);
	pthread_mutex_unlock(&philo->info->m_stop);
	return (NULL);
}

void	grab_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print(philo, " has taken a fork\n");
	
	if (philo->info->philo_nb == 1)
	{
		ft_usleep(philo->info->time2_die);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	print(philo, " has taken a fork\n");
}

