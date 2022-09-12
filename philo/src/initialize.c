/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 10:14:53 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/09/12 15:33:17 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "../include/philo.h"

bool	init_info_mutexes(t_info *info)
{
	if (pthread_mutex_init(&info->info_lock, 0) != 0)
		return (false);
	if (pthread_mutex_init(&info->write_lock, 0))
	{
		pthread_mutex_destroy(&info->info_lock);
		return (false);
	}
	return (true);
}

bool	init_forks(t_info *info)
{
	int	i;

	info->forks = malloc(sizeof(pthread_mutex_t) * info->nr_philos);
	if (!info->forks)
		return (false);
	i = 0;
	while (i < info->nr_philos)
	{
		if(pthread_mutex_init(&info->forks[i], 0) != 0)
			return (false);
		i++;
	}
	return (true);
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
	if(!info->philos)
		return (false);
	i = 0;
	while (i <= info->nr_philos)
	{
		info->philos[i].info = info;
		info->philos[i].index = i + 1;
		info->philos[i].nr_of_eats = 0;
		info->philos[i].time_to_death = info->time_to_die;
		set_philo_fork_ids(&info->philos[i]);
		i++;
	}
	return (true);
}