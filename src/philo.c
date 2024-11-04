/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:22:59 by ededemog          #+#    #+#             */
/*   Updated: 2024/11/04 15:13:55 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_death(void *ph)
{
	t_philo	*philo = (t_philo *)ph;
	ft_usleep(philo->info->time2_die + 1);

	pthread_mutex_lock(&philo->info->m_eat);
	pthread_mutex_lock(&philo)
}