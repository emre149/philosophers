/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 08:29:19 by ededemog          #+#    #+#             */
/*   Updated: 2024/12/02 11:18:27 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

bool	safe_stop(t_info *info)
{
	bool	stop;

	pthread_mutex_lock(&info->m_stop);
	stop = info->stop;
	pthread_mutex_unlock(&info->m_stop);
	return (stop);
}

bool	is_dead(t_philo *philo, int i)
{
	bool	stop;

	pthread_mutex_lock(&philo->info->m_stop);
	if (i)
		philo->info->stop = true;
	stop = philo->info->stop;
	pthread_mutex_unlock(&philo->info->m_stop);
	return (stop);
}

void	ft_fprintf(char *msg)
{
	size_t	i;

	i = 0;
	while (msg[i])
		i++;
	write(2, msg, i);
}
