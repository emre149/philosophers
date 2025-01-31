/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:48:12 by ededemog          #+#    #+#             */
/*   Updated: 2025/01/31 19:26:12 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static char	*ft_trim_whitespace(char *str)
{
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r')
		++str;
	return (str);
}

static int	check_negative(char *str, int *err)
{
	if (*str == '-')
	{
		*err = 1;
		printf("invalid argument\n");
		return (1);
	}
	return (0);
}

static int	str_to_int(char *str, int *err)
{
	long	res;

	res = 0;
	str = ft_trim_whitespace(str);
	if (check_negative(str, err))
		return (1);
	if (*str == '+')
		++str;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str++ - '0';
		if (res > 2147483647)
		{
			printf("invalid argument\n");
			*err = 1;
			return (1);
		}
	}
	if (*str || res == 0)
	{
		printf("invalid argument\n");
		*err = 1;
		return (1);
	}
	return ((int)res);
}

int	parser(t_main *main, char **str, int ac)
{
	int	err;

	err = 0;
	if (ac < 5 || ac > 6)
	{
		printf("invalid number of arguments\n");
		return (1);
	}
	main->nb_philo = str_to_int(str[1], &err);
	main->time_to_die = str_to_int(str[2], &err);
	main->time_to_eat = str_to_int(str[3], &err);
	main->time_to_sleep = str_to_int(str[4], &err);
	if (ac == 6)
		main->nb_meals = str_to_int(str[5], &err);
	else
		main->nb_meals = -1;
	if (err)
		return (1);
	return (0);
}
