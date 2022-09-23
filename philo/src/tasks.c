/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tasks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/19 13:51:52 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/09/23 17:37:12 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	take_forks(t_philo *philo)
{
	int		index;

	index = philo->index;
	pthread_mutex_lock(&philo->info->forks[philo->fork_left]);
	if (!is_done(philo->info))
		write_message(get_elapsed_time(philo->info), TAKE_FORK, index);
	pthread_mutex_lock(&philo->info->forks[philo->fork_right]);
	if (!is_done(philo->info))
		write_message(get_elapsed_time(philo->info), TAKE_FORK, index);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->info->forks[philo->fork_left]);
	pthread_mutex_unlock(&philo->info->forks[philo->fork_right]);
}

bool	philo_think(t_philo *philo)
{
	long	time_to_think;
	long	wait_start;
	long	time_last_meal;

	wait_start = get_elapsed_time(philo->info);
	pthread_mutex_lock(&philo->philo_lock);
	time_last_meal = philo->time_last_meal;
	pthread_mutex_unlock(&philo->philo_lock);
	time_to_think = (philo->info->time_to_die
			- (wait_start - time_last_meal)
			- philo->info->time_to_eat) / 2;
	if (time_to_think > 1000)
		time_to_think = 500;
	if (!wait_action(philo, THINK, time_to_think))
		return (false);
	return (true);
}

bool	philo_sleep(t_philo *philo)
{
	if (philo->info->time_to_sleep == 0)
	{
		if (is_done(philo->info))
			return (false);
		write_message(get_elapsed_time(philo->info), SLEEP, philo->index);
	}
	else if (!wait_action(philo, SLEEP, philo->info->time_to_sleep))
		return (false);
	return (true);
}

bool	philo_eat(t_philo *philo)
{
	bool	success;

	take_forks(philo);
	pthread_mutex_lock(&philo->philo_lock);
	philo->time_last_meal = get_elapsed_time(philo->info);
	pthread_mutex_unlock(&philo->philo_lock);
	success = wait_action(philo, EAT, philo->info->time_to_eat);
	drop_forks(philo);
	if (success)
	{
		pthread_mutex_lock(&philo->philo_lock);
		philo->nr_of_eats++;
		pthread_mutex_unlock(&philo->philo_lock);
		if (philo->nr_of_eats == philo->info->nr_times_to_eat)
		{
			pthread_mutex_lock(&philo->info->info_lock);
			philo->info->nr_fully_fed_philo++;
			pthread_mutex_unlock(&philo->info->info_lock);
		}
	}
	return (success);
}
