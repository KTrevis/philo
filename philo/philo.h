/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:17:22 by ketrevis          #+#    #+#             */
/*   Updated: 2024/01/25 13:23:33 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>
# include <unistd.h>

typedef enum s_states
{
	EATING,
	THINKING,
	SLEEPING,
}	t_states;

typedef struct s_args
{
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				start_time;
	int				max_eat_count;
	bool			stop;
	pthread_mutex_t	routine_start;
	pthread_mutex_t	time_mutex;
	pthread_mutex_t	stdo_mutex;
}	t_args;

typedef struct s_philo
{
	int				id;
	int				last_eat;
	int				eat_count;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
	t_args			*args;
	t_states		state;
}	t_philo;

int		get_curr_time(t_philo *philo);
t_philo	*init(char **av);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
void	*routine(void *arg);
int		create_threads(t_philo *philos, uint size);
int		print_state(t_philo *philo);
int		print_fork_pickup(t_philo *philo);
void	init_odd_philo(t_philo *philo);

#endif
