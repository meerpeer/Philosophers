/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 11:20:16 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/09/29 14:08:20 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	is_done(t_info *info)
{
	bool	done;

	if (info->time_to_die == 0)
		return (true);
	pthread_mutex_lock(&info->info_lock);
	if (info->nr_fully_fed_philo == info->nr_philos)
		info->done = true;
	done = info->done;
	pthread_mutex_unlock(&info->info_lock);
	return (done);
}

bool	wait_action(t_philo *philo, t_action ACTION, long wait_time)
{
	long	wait_start;
	long	wait_end;

	if (!try_write_message(philo->info, ACTION, philo->index))
		return (false);
	wait_start = get_elapsed_time(philo->info);
	wait_end = wait_start + wait_time;
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
	if (!try_write_message(philo->info, TAKE_FORK, 1)
		&& philo->info->time_to_die != 0)
		return ;
	while (true)
	{
		if (is_done(philo->info))
			return ;
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
