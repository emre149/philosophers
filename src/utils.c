/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:26:59 by ededemog          #+#    #+#             */
/*   Updated: 2024/11/08 16:43:33 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	i;
	int	nb;
	int	sign;

	i = 0;
	nb = 0;
	sign = 1;

	while (str[i] && str[i] <= 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	return (nb * sign);
}

void	ft_usleep(int ms)
{
	long int	time;

	time = get_time();
	while (get_time() - time < ms)
		usleep(ms / 10);
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void print(t_philo *philo, char *str)
{
    long int	time;

    pthread_mutex_lock(&(philo->info->print));
    time = get_time() - philo->info->start;
    if (!philo->info->stop && time >= 0 && time <= INT_MAX && !is_dead(philo, 0)) {
        printf("%ld %d %s", get_time() - philo->info->start, philo->id, str);
    }
    pthread_mutex_unlock(&(philo->info->print));
}

long int	get_time(void)
{
	struct timeval tv;
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
	pthread_mutex_lock(&philo->info->dead);
	if (i)
		philo->is_eating = true;
	if (philo->info->stop)
	{
		pthread_mutex_unlock(&philo->info->dead);
		return (true);
	}
	pthread_mutex_unlock(&philo->info->dead);
	return (false);
}
