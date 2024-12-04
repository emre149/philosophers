/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:29:29 by ededemog          #+#    #+#             */
/*   Updated: 2024/12/04 13:12:39 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_global_mutex(t_info *info)
{
	pthread_mutex_unlock(&info->m_stop);
	pthread_mutex_unlock(&info->m_eat);
	pthread_mutex_unlock(&info->dead);
	pthread_mutex_unlock(&info->print);	
	pthread_mutex_destroy(&info->m_stop);
	pthread_mutex_destroy(&info->m_eat);
	pthread_mutex_destroy(&info->dead);
	pthread_mutex_destroy(&info->print);
}

void	destroy_philo_mutex(t_info *info, int i)
{
	while (i >= 0)
	{
		pthread_mutex_unlock(&info->philo[i].left_fork);
		pthread_mutex_unlock(info->philo[i].right_fork);
		pthread_mutex_destroy(&info->philo[i].left_fork);
		pthread_mutex_destroy(&info->philo[i].meal_lock);
		i--;		
	}
}

int	cleanup(t_info	*info, int i, bool free_philo)
{
	if (i >= 0)
		destroy_philo_mutex(info, i);
	destroy_global_mutex(info);
	if (free_philo && info->philo)
		free(info->philo);
	return (0);
}
