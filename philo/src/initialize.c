/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 10:14:53 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/09/15 13:27:39 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_forks(t_info *info)
{
	int	i;

	info->forks = malloc(sizeof(pthread_mutex_t) * info->nr_philos);
	if (!info->forks)
		return (0);
	i = 0;
	while (i < info->nr_philos)
	{
		if (pthread_mutex_init(&info->forks[i], 0) != 0)
			return (i);
		i++;
	}
	return (i);
}

static void	set_philo_fork_ids(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->index - 1;
	right = philo->index;
	if (right >= philo->info->nr_philos)
		right = 0;
	philo->fork_id1 = left;
	philo->fork_id2 = right;
}

bool	init_philos(t_info *info)
{
	int	i;

	info->philos = malloc(sizeof(*info->philos) * info->nr_philos);
	if (!info->philos)
		return (false);
	i = 0;
	while (i <= info->nr_philos)
	{
		info->philos[i].info = info;
		info->philos[i].index = i + 1;
		info->philos[i].nr_of_eats = 0;
		info->philos[i].time_to_death = info->time_to_die + info->start_time;
		set_philo_fork_ids(&info->philos[i]);
		i++;
	}
	return (true);
}

int	init_philos_mutexes(t_info	*info)
{
	int	i;

	i = 0;
	while (i <= info->nr_philos)
	{
		if (pthread_mutex_init(&info->philos[i].philo_lock, 0) != 0)
			return (i);
		i++;
	}
	return (i);
}

bool	initialize_mutexes(t_info *info)
{
	int		nr_forks;
	int		nr_philo_locks;
	bool	completed;

	nr_forks = 0;
	nr_philo_locks = 0;
	completed = true;
	if (!info)
		return (false);
	nr_forks = init_forks(info);
	if (nr_forks < info->nr_philos)
		completed = false;
	else
	{
		nr_philo_locks = init_philos_mutexes(info);
		if (nr_philo_locks < info->nr_philos)
			completed = false;
		if (pthread_mutex_init(&info->info_lock, 0) != 0)
			completed = false;
	}
	if (completed)
		return (true);
	destroy_mutexes(info, nr_forks, nr_philo_locks, false);
	free_info_contents(info);
	return (false);
}
