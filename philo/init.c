/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:42:45 by ketrevis          #+#    #+#             */
/*   Updated: 2024/01/25 13:38:43 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

static void	link_forks(t_philo *philos)
{
	int	i;

	i = 0;
	if (philos[i + 1].id == 0)
		return ;
	while (philos[i].id)
	{
		if (philos[i + 1].id == 0)
			philos[i].r_fork = &philos[0].l_fork;
		else
			philos[i].r_fork = &philos[i + 1].l_fork;
		i++;
	}
}

static t_philo	*init_philos(int size)
{
	t_philo	*philos;
	int		i;

	if (size <= 0)
		return (NULL);
	philos = ft_calloc((size + 1), sizeof(t_philo));
	if (!philos)
		return (NULL);
	i = 0;
	while (i < size)
	{
		philos[i].id = i + 1;
		if (pthread_mutex_init(&philos[i].l_fork, NULL))
			return (free(philos), NULL);
		i++;
	}
	philos[i].id = 0;
	link_forks(philos);
	return (philos);
}

static int	init_args_mutexes(t_args *args)
{
	if (pthread_mutex_init(&args->time_mutex, NULL))
		return (0);
	if (pthread_mutex_init(&args->routine_start, NULL))
		return (pthread_mutex_destroy(&args->time_mutex), 0);
	if (pthread_mutex_init(&args->stdo_mutex, NULL))
		return (pthread_mutex_destroy(&args->routine_start),
			pthread_mutex_destroy(&args->time_mutex), 0);
	if (args->time_to_die <= 0 || args->time_to_eat <= 0
		|| args->time_to_sleep <= 0)
		return (0);
	return (1);
}

static t_args	*init_args(char **av)
{
	t_args	*args;

	args = ft_calloc(sizeof(t_args), 1);
	if (!args)
		return (NULL);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]) * 1000;
	args->time_to_sleep = ft_atoi(av[4]) * 1000;
	if (av[5])
	{
		args->max_eat_count = ft_atoi(av[5]);
		if (args->max_eat_count <= 0)
			return (free(args), NULL);
	}
	if (!init_args_mutexes(args))
		return (free(args), NULL);
	return (args);
}

t_philo	*init(char **av)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = init_philos(ft_atoi(av[1]));
	if (!philos)
		return (NULL);
	philos->args = init_args(av);
	if (!philos->args)
		return (free(philos), NULL);
	while (philos[i].id)
	{
		philos[i].args = philos->args;
		i++;
	}
	return (philos);
}
