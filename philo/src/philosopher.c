/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 11:20:16 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/09/19 13:36:44 by mevan-de      ########   odam.nl         */
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

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->info->forks[philo->fork_left]);
	pthread_mutex_unlock(&philo->info->forks[philo->fork_right]);
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
				- philo->info->time_to_eat)
				/ 2;
	if (!wait_action(philo, THINK, time_to_think))
		return (false);
	return (true);
}

bool	philo_sleep(t_philo *philo)
{
	if(!wait_action(philo, SLEEP, philo->info->time_to_sleep))
		return (false);
	return (true);
}

bool	philo_eat(t_philo *philo)
{
	bool	success;

	take_forks(philo);
	success = wait_action(philo, EAT, philo->info->time_to_eat);
	drop_forks(philo);
	pthread_mutex_lock(&philo->philo_lock);
	philo->time_last_meal = get_elapsed_time(philo->info);
	philo->nr_of_eats++;
	if (philo->nr_of_eats == philo->info->nr_times_to_eat)
	{
		pthread_mutex_lock(&philo->info->info_lock);
		philo->info->nr_fully_fed_philo++;
		pthread_mutex_unlock(&philo->info->info_lock);
	}
	pthread_mutex_unlock(&philo->philo_lock);
	return (success);
}

void	*philosopher(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->index % 2 == 1)
	{
		if(!philo_think(philo))
			return (NULL);
	}
	while (true)
	{
		if (is_done(philo->info))
			return (NULL);
		if(!philo_eat(philo))
			return (NULL);
		if(!philo_sleep(philo))
			return (NULL);
		if(!philo_think(philo))
			return (NULL); 
	}
	return (NULL);
}
