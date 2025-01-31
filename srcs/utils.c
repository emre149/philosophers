/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:48:21 by ededemog          #+#    #+#             */
/*   Updated: 2025/01/31 19:25:25 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	print(t_philo *philo, char *str, int flag)
{
	size_t	time;

	pthread_mutex_lock(&philo->main->lock);
	if (flag)
	{
		philo->main->stop = 1;
		time = get_current_time() - philo->main->start_time;
		printf("%zu %d %s\n", time, philo->id, str);
	}
	if (philo->main->stop)
	{
		pthread_mutex_unlock(&philo->main->lock);
		return ;
	}
	time = get_current_time() - philo->main->start_time;
	printf("%lu %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->main->lock);
}

int	check_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->main->lock);
	if (philo->main->stop)
	{
		pthread_mutex_unlock(&philo->main->lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->main->lock);
	return (0);
}

int	philo_pause(size_t ms, t_philo *philo)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < ms)
	{
		usleep(500);
		if (check_stop(philo))
			return (1);
		usleep(100);
	}
	return (0);
}
