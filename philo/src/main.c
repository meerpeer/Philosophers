/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 17:03:08 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/09/12 16:03:52 by mevan-de      ########   odam.nl         */
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
		pthread_join(info->philos[i_threads].thread, NULL);
	}
	destroy_forks(info, info->nr_philos);
	pthread_mutex_destroy(&info->info_lock);
	pthread_mutex_destroy(&info->write_lock);
	free_info_contents(info);
}

/**
	@brief A function that checks the state of all philos and determines
	when the philosophers should stop
*/
void	loop(t_info *info)
{
	int	i;
	int	nr_full_philos;

	while (!info->done)
	{
		i = 0;
		nr_full_philos = 0;
		while (i < info->nr_philos)
		{
			if(info->nr_times_to_eat > 0
				&& info->philos->nr_of_eats >= info->nr_times_to_eat)
				nr_full_philos++;
			if (nr_full_philos == info->nr_philos)
			{
				//write message that everyone is full??
				info->done = true;
			}
			else if(info->philos[i].time_to_death < info->time_to_eat)
			{
				//write a message that this boy has died
				info->done = true;
			}
			i++;
		}
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
	while (i < info->nr_philos)
	{
		pthread_create(&info->philos[i].thread, NULL,
			philosopher, &info->philos[i]);
		i++;
	}
	if (i == info->nr_philos)
		loop(info);
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
	if (!init_forks(&info))
		return (EXIT_FAILURE);
	if (!init_philos(&info))
		return (destroy_forks(&info, info.nr_philos),
			EXIT_FAILURE);
	if (!init_info_mutexes(&info))
		return (destroy_forks(&info, info.nr_philos),
			EXIT_FAILURE);
	start(&info);
	return (0);
}
