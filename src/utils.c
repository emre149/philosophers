/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:26:59 by ededemog          #+#    #+#             */
/*   Updated: 2024/12/21 00:16:49 by ededemog         ###   ########.fr       */
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
	long int	start;
	long int	current;
	long int	elapsed;

	start = get_time();
	while (1)
	{
		current = get_time();
		elapsed = current - start;
		if (elapsed >= ms)
			break;
		if (ms - elapsed > 1)
			usleep(500);
		else
			usleep(100);
	}
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	print(t_philo *philo, char *str)
{
	long long int	time;
	bool			should_print;

	pthread_mutex_lock(&(philo->info->m_stop));
	should_print = !philo->info->stop;
	pthread_mutex_unlock(&(philo->info->m_stop));
	if (!should_print)
		return ;
	pthread_mutex_lock(&(philo->info->print));
	time = get_time() - philo->info->start;
	if (time >= 0 && time <= INT_MAX)
		printf("%lld %d %s", time, philo->id, str);
	pthread_mutex_unlock(&(philo->info->print));
}
