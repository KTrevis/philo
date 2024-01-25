/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:42:57 by ketrevis          #+#    #+#             */
/*   Updated: 2024/01/25 16:55:25 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

static void	destroy_mutexes(t_philo *philos)
{
	int	i;

	i = 0;
	while (philos[i].id)
	{
		pthread_mutex_destroy(&philos[i].l_fork);
		i++;
	}
	pthread_mutex_destroy(&philos->args->routine_start);
	pthread_mutex_destroy(&philos->args->time_mutex);
	pthread_mutex_destroy(&philos->args->stdo_mutex);
}

void	free_philo(t_philo *philo)
{
	destroy_mutexes(philo);
	free(philo->args);
	free(philo);
}

int	main(int ac, char **av)
{
	t_philo	*philos;

	if (ac != 5 && ac != 6)
	{
		printf("Error\n");
		return (0);
	}
	philos = init(av);
	if (!philos)
	{
		printf("Error\n");
		return (0);
	}
	if (!create_threads(philos, ft_atoi(av[1])))
		return (free_philo(philos), 0);
	free_philo(philos);
}
