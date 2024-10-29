/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:22:59 by ededemog          #+#    #+#             */
/*   Updated: 2024/10/29 19:29:17 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	monitor_health(t_philo *philo)
{
	if (timestamp() - philo->last_meal >= philo->info->time2_die)
	{
		p_print(philo, "died miskine\n");
		pthread_mutex_lock(&philo->info->m_stop);
		philo->info->stop = 1;
		pthread_mutex_unlock(&philo->info->m_stop);
	}
}