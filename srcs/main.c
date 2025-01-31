/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:48:07 by ededemog          #+#    #+#             */
/*   Updated: 2025/01/31 18:31:29 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	main(int ac, char **av)
{
	t_main	main;

	if (parser(&main, av, ac))
		return (1);
	if (init(&main))
		return (1);
	if (start(&main))
		return (1);
	monitor(&main);
	return (0);
}
