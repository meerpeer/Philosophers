/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 17:03:08 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/09/12 14:42:41 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
	A function to stop everything and to clean up, it should: 
		- Destroy all mutexes (fork / write/ master checker)
		- Free philosophers and forks (check if more is malloced)
		- Wait for all threads to close with pthreadjoin
			- i_threads = ammount of threads created
*/
void	stop(t_info *info, int i_threads)
{
	while (i_threads > 0)
	{
		i_threads--;
		pthread_join(info->philos[i_threads].thread, NULL);
	}
	destroy_mutex_array(info->forks, info->nr_philos);
	pthread_mutex_destroy(&info->done_lock);
	free_info_contents(info);
}

/*
	A function that checks the state of all philos and determines
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
		usleep(1000);
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

	if(argc < 5 || argc > 6)
		return (1);
	if (!parse_input_to_info(argc, argv, &info))
		return (EXIT_FAILURE);
	info.nr_fully_fed_philo = 0;
	info.done = false;
	if(!init_forks(&info))
		return (EXIT_FAILURE);
	if(!init_philos(&info))
		return (EXIT_FAILURE);
	if(pthread_mutex_init(&info.done_lock, 0) != 0)
	{
		destroy_mutex_array(info.forks, info.nr_philos);
		free_info_contents(&info);
		return (EXIT_FAILURE);
	}
	start(&info);
	return (0);
}
