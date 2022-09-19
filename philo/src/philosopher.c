/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 11:20:16 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/09/19 14:14:14 by mevan-de      ########   odam.nl         */
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

bool	wait_action(t_philo *philo, t_action ACTION, long wait_time)
{
	long	wait_start;
	long	wait_end;

	wait_start = get_elapsed_time(philo->info);
	if (is_done(philo->info))
		return (false);
	wait_end = wait_start + wait_time;
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
	{
		if (!philo_think(philo))
			return (NULL);
	}
	while (true)
	{
		if (is_done(philo->info))
			return (NULL);
		if (!philo_eat(philo))
			return (NULL);
		if (!philo_sleep(philo))
			return (NULL);
		if (!philo_think(philo))
			return (NULL);
	}
	return (NULL);
}
