/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:19:10 by ededemog          #+#    #+#             */
/*   Updated: 2024/10/29 19:29:51 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_init(t_info *data)
{
	int	i;

	i = 0;
	data->start = timestamp();
	while (i < data->philo_nb)
	{
		data->philo[i].id = i + 1;
		data->philo[i].last_meal = 0;
		data->philo[i].nb_meals = 0;
		data->philo[i].info = data;
		data->philo[i].right_fork = NULL;
		pthread_mutex_init(&(data->philo[i].left_fork), NULL);
		if (i == data->philo_nb - 1)
			data->philo[i].right_fork = &(data->philo[0].left_fork);
		else
			data->philo[i].right_fork = &(data->philo[i + 1].left_fork);
		if (pthread_create(&data->philo[i].thread, NULL, &lifetime, &(data->philo[i])) != 0)
			return (-1);
		i++;
	}
	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}