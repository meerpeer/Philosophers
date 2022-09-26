/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 17:03:08 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/09/26 10:31:04 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	stop(t_info *info, int i_threads)
{
	while (i_threads > 0)
	{
		i_threads--;
		pthread_join(info->philo_threads[i_threads], NULL);
	}
	destroy_mutexes(info, info->nr_philos, info->nr_philos, true);
	free_info_contents(info);
}

bool	has_one_died(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nr_philos)
	{
		pthread_mutex_lock(&info->philos[i].philo_lock);
		if (get_elapsed_time(info)
			>= (info->philos[i].time_last_meal + info->time_to_die))
		{
			pthread_mutex_lock(&info->info_lock);
			if (!info->done)
				write_message(get_elapsed_time(info), DIE,
					info->philos[i].index);
			info->done = true;
			pthread_mutex_unlock(&info->info_lock);
			pthread_mutex_unlock(&info->philos[i].philo_lock);
			return (true);
		}
		pthread_mutex_unlock(&info->philos[i].philo_lock);
		i++;
	}
	return (false);
}

void	loop(t_info *info)
{
	while (true)
	{
		if (has_one_died(info))
			break ;
		pthread_mutex_lock(&info->info_lock);
		if (info->nr_fully_fed_philo == info->nr_philos)
		{
			info->done = true;
			pthread_mutex_unlock(&info->info_lock);
			break ;
		}
		pthread_mutex_unlock(&info->info_lock);
		usleep(250);
	}
}

void	start(t_info *info)
{
	int	i;

	i = 0;
	info->philo_threads = malloc(sizeof(pthread_mutex_t) * info->nr_philos);
	while (i < info->nr_philos)
	{
		if (pthread_create(&info->philo_threads[i], NULL,
				philosopher, &info->philos[i]) != 0)
			break ;
		i++;
	}
	if (i == info->nr_philos && info->nr_times_to_eat != 0)
		loop(info);
	pthread_mutex_lock(&info->info_lock);
	info->done = true;
	pthread_mutex_unlock(&info->info_lock);
	stop(info, i);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc < 5 || argc > 6)
		return (1);
	if (!parse_input_to_info(argc, argv, &info))
		return (EXIT_FAILURE);
	info.nr_fully_fed_philo = 0;
	info.done = false;
	info.start_delay = 200;
	info.start_time = get_time_in_ms() + info.start_delay;
	if (!init_philos(&info))
		return (EXIT_FAILURE);
	if (!initialize_mutexes(&info))
		return (EXIT_FAILURE);
	start(&info);
	return (0);
}
