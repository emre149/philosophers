/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:48:02 by ededemog          #+#    #+#             */
/*   Updated: 2025/01/31 19:25:58 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	join_threads(t_main *main, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		pthread_join(main->philos[i].thread, NULL);
		i++;
	}
}

void	clean(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->nb_philo)
		pthread_mutex_destroy(&main->forks[i++]);
	pthread_mutex_destroy(&main->lock);
	free(main->philos);
	free(main->forks);
}
