/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 11:20:16 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/09/26 10:32:41 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	is_done(t_info *info)
{
	bool	done;

	if (info->time_to_die == 0)
		return (true);
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
		if (get_elapsed_time(philo->info) >= wait_end)
			return (true);
		usleep(250);
	}
}

void	single_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->forks[philo->fork_left]);
	if (!is_done(philo->info) && philo->info->time_to_die != 0)
		write_message(get_elapsed_time(philo->info), TAKE_FORK, 1);
	while (true)
	{
		if (is_done(philo->info))
		{
			pthread_mutex_unlock(&philo->info->forks[philo->fork_left]);
			return ;
		}
		usleep (250);
	}
}

void	*philosopher(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (philo->info->start_time > get_time_in_ms())
		continue ;
	if (philo->info->nr_philos == 1)
		return (single_philo(philo), NULL);
	else if (philo->index % 2 == 1)
	{
		if (!philo_think(philo))
			return (NULL);
	}
	while (true)
	{
		if (is_done(philo->info))
			break ;
		if (!philo_eat(philo))
			break ;
		if (!philo_sleep(philo))
			break ;
		if (!philo_think(philo))
			break ;
	}
	return (NULL);
}
