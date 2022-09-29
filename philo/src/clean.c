/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 11:34:54 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/09/29 13:13:43 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	destroy_philo_mutexes(t_info *info, int n)
{
	bool	completed;

	completed = true;
	while (n > 0)
	{
		n--;
		if (pthread_mutex_destroy(&info->philos[n].philo_lock) != 0)
			completed = false;
	}
	return (completed);
}

bool	destroy_forks(t_info *info, int n)
{
	bool	completed;

	completed = true;
	while (n > 0)
	{
		n--;
		if (pthread_mutex_destroy(&info->forks[n]) != 0)
			completed = false;
	}
	return (completed);
}

bool	destroy_mutexes(t_info *info, int fork_mutexes, int philo_mutexes,
	bool info_locks_created)
{
	bool	completed;

	completed = true;
	if (!destroy_forks(info, fork_mutexes))
		completed = false;
	if (!destroy_philo_mutexes(info, philo_mutexes))
		completed = false;
	if (info_locks_created)
	{
		if (pthread_mutex_destroy(&info->info_lock) != 0)
			completed = false;
		if (pthread_mutex_destroy(&info->write_lock) != 0)
			completed = false;
	}
	return (completed);
}

void	free_info_contents(t_info *info)
{
	if (!info)
		return ;
	if (info->forks)
		free (info->forks);
	if (info->philos)
		free(info->philos);
	if (info->philo_threads)
		free(info->philo_threads);
}
