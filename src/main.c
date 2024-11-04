/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:37:46 by ededemog          #+#    #+#             */
/*   Updated: 2024/11/04 15:11:18 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->philo_nb)
	{
		pthread_mutex_destroy(&info->philo[i].left_fork);
		pthread_mutex_destroy(&info->philo[i].meal_lock);
		i++;
	}
	free(info->philo);
	destroy_global_mutex(info);
}

int	main(int ac, char **av)
{
	t_info	info;

	if (!parsing(ac, av, &info))
		return (1);

	free_all(&info);
	return (0);
}