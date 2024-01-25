/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:09:59 by ketrevis          #+#    #+#             */
/*   Updated: 2024/01/25 16:55:48 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

static int	everyone_ate(t_philo *philos)
{
	int	i;
	int	count;

	if (philos->args->max_eat_count == 0)
		return (0);
	i = 0;
	count = 0;
	pthread_mutex_lock(&philos->args->stdo_mutex);
	while (philos[i].id)
	{
		if (philos[i].eat_count >= philos->args->max_eat_count)
			count++;
		i++;
	}
	if (count == i)
	{
		printf("Everyone ate %u times\n", philos->args->max_eat_count);
		philos->args->stop = true;
	}
	pthread_mutex_unlock(&philos->args->stdo_mutex);
	return (count == i);
}

static int	philo_died(t_philo *philos)
{
	int	i;
	int	curr_time;

	i = 0;
	while (philos[i].id)
	{
		pthread_mutex_lock(&philos->args->stdo_mutex);
		curr_time = get_curr_time(philos);
		if (curr_time - philos[i].last_eat >= philos->args->time_to_die)
		{
			philos->args->stop = true;
			printf("%u %u died\n", curr_time - philos->args->start_time,
				philos[i].id);
			pthread_mutex_unlock(&philos->args->stdo_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philos->args->stdo_mutex);
		i++;
	}
	return (0);
}

static void	wait_threads(pthread_t *t_ids, t_philo *philos)
{
	int	i;

	i = 0;
	while (philos[i].id)
	{
		pthread_join(t_ids[i], NULL);
		i++;
	}
	free(t_ids);
}

static void	init_last_eat(t_philo *philos)
{
	int	i;

	i = 0;
	while (philos[i].id)
	{
		philos[i].last_eat = philos->args->start_time;
		i++;
	}
}

int	create_threads(t_philo *philos, uint size)
{
	int			i;
	pthread_t	*t_ids;

	i = 0;
	t_ids = ft_calloc(size, sizeof(pthread_t));
	if (!t_ids)
		return (0);
	pthread_mutex_lock(&philos->args->routine_start);
	while (philos[i].id)
	{
		if (pthread_create(t_ids + i, NULL, routine, philos + i))
			return (free(t_ids), 0);
		i++;
	}
	philos->args->start_time = get_curr_time(philos);
	init_last_eat(philos);
	pthread_mutex_unlock(&philos->args->routine_start);
	while (1)
	{
		if (philo_died(philos) || everyone_ate(philos))
			break ;
		usleep(100);
	}
	wait_threads(t_ids, philos);
	return (1);
}
