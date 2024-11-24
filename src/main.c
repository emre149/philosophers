/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:37:46 by ededemog          #+#    #+#             */
/*   Updated: 2024/11/11 23:19:31 by ededemog         ###   ########.fr       */
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

int main(int ac, char **av)
{
    t_info info;
    pthread_t *threads;
    int i;

    if (!parsing(ac, av, &info))
        return (1);

    info.start = get_time();

    if (!philo_init(&info))
    {
        free_all(&info);
        return (1);
    }

    threads = malloc(sizeof(pthread_t) * info.philo_nb);
    if (!threads)
    {
        free_all(&info);
        return (1);
    }

    // Create threads for each philosopher using a while loop
    i = 0;
    while (i < info.philo_nb)
    {
        if (pthread_create(&threads[i], NULL, life, &info.philo[i]) != 0)
        {
            free_all(&info);
            free(threads);
            return (1);
        }
        i++;
    }

    // Join threads using a while loop
    i = 0;
    while (i < info.philo_nb)
    {
        pthread_join(threads[i], NULL);
        i++;
    }

    free(threads);
    free_all(&info);
    return (0);
}