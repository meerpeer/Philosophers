/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 10:14:53 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/09/30 12:35:19 by mevan-de      ########   odam.nl         */
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
	philo->fork_first = philo->index - 1;
	philo->fork_second = philo->index % (philo->info->nr_philos + 1);
	if (philo->info->nr_philos == 1)
		philo->fork_second = 0;
	if (philo->index % 2 == 0)
	{
		philo->fork_first = philo->index % (philo->info->nr_philos + 1);
		philo->fork_second = philo->index - 1;
	}
}

bool	init_philos(t_info *info)
{
	int	i;

	info->philos = malloc(sizeof(*info->philos) * (info->nr_philos + 1));
	if (!info->philos)
		return (false);
	i = 0;
	while (i <= info->nr_philos)
	{
		info->philos[i].info = info;
		info->philos[i].index = i + 1;
		info->philos[i].nr_of_eats = 0;
		info->philos[i].time_last_meal = 0;
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
	nr_philo_locks = init_philos_mutexes(info);
	if (nr_forks < info->nr_philos || nr_philo_locks < info->nr_philos)
		completed = false;
	if (pthread_mutex_init(&info->info_lock, 0) != 0)
		completed = false;
	else if (pthread_mutex_init(&info->write_lock, 0) != 0)
	{
		completed = false;
		pthread_mutex_destroy(&info->info_lock);
	}
	if (completed)
		return (true);
	destroy_mutexes(info, nr_forks, nr_philo_locks, false);
	free_info_contents(info);
	return (false);
}
