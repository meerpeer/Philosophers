/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 11:20:16 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/09/19 11:54:23 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	is_done(t_info *info)
{
	bool	done;

	pthread_mutex_lock(&info->info_lock);
	done = info->done;
	pthread_mutex_unlock(&info->info_lock);
	return (done);
}

void	take_forks(t_philo *philo)
{
	if (philo->index % 2 == 1)
	{
		pthread_mutex_lock(&philo->info->forks[philo->fork_left]);
		pthread_mutex_lock(&philo->info->forks[philo->fork_right]);
	}
	else
	{
		pthread_mutex_lock(&philo->info->forks[philo->fork_right]);
		pthread_mutex_lock(&philo->info->forks[philo->fork_left]);
	}
}

//wait (sleep or think)
bool	wait_action(t_philo *philo, t_action ACTION)
{
	long	wait_start;
	long	wait_end;

	wait_start = get_elapsed_time(philo->info);
	if (is_done(philo->info))
		return (false);
	wait_end = wait_start + philo->info->time_to_sleep;
	if (ACTION == THINK)
	{
		pthread_mutex_lock(&philo->philo_lock);
		wait_end = (philo->info->time_to_die
				- (wait_start - philo->time_last_meal)
				- philo->info->time_to_eat) / 2;
		pthread_mutex_unlock(&philo->philo_lock);
	}
	write_message(get_elapsed_time(philo->info), ACTION, philo->index);
	while (true)
	{
		if (is_done(philo->info))
			return (false);
		if (get_elapsed_time(philo->info) > wait_end)
			return (true);
		usleep(250);
	}
}

void	*philosopher(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->index % 2 == 1)
		wait_action(philo, THINK);
	while (true)
	{
		if (is_done(philo->info))
			return (NULL);
		usleep (250);
	}
	(void) data;
	return (NULL);
}
