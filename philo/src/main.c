/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 17:03:08 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/09/20 15:33:09 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**
	@brief A function to stop everything and to clean up, it should: 
		Destroy all mutexes (forks / write/ info) 
		Free philosophers and forks (check if more is malloced) 
		Wait for all existing threads to close with pthread join 
		@param info info data struct
		@param i_threads amount of threads created
*/
void	stop(t_info *info, int i_threads)
{
	while (i_threads > 0)
	{
		i_threads--;
		printf("index = %i\n" , i_threads);
		if (pthread_join(info->philo_threads[i_threads], NULL) != 0)
			return ;
	}
	destroy_mutexes(info, info->nr_philos, info->nr_philos, true);
	free_info_contents(info);
}

bool	has_one_died(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nr_philos && !info->done)
	{
		pthread_mutex_lock(&info->philos[i].philo_lock);
		if (get_elapsed_time(info)
			>= (info->philos[i].time_last_meal + info->time_to_die))
		{
			info->done = true;
			write_message(get_elapsed_time(info), DIE, info->philos[i].index);
			return (true);
		}
		pthread_mutex_unlock(&info->philos[i].philo_lock);
		i++;
	}
	return (false);
}

/**
	@brief A function that checks the state of all philos and determines
	when the philosophers should stop
*/
void	loop(t_info *info)
{
	bool	done;

	done = has_one_died(info);
	while (!done)
	{
		pthread_mutex_lock(&info->info_lock);
		if (info->done)
			done = true;
		else
		{
			done = has_one_died(info);
			if (done)
				info->done = true;
		}
		pthread_mutex_unlock(&info->info_lock);
		usleep(250);
	}
}

/*
	Creating all philosopher threads and init the loop
	when the loop exits, it should stop and clean up
*/
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
	if (i == info->nr_philos)
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
