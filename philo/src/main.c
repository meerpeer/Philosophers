/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 17:03:08 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/09/08 17:18:45 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_info	info;

	if(argc < 5 || argc > 6)
		return (1);
	info.nr_philos = parse_arg_to_long(argv[1], INT_MAX);
	info.time_to_die = parse_arg_to_long(argv[2], LONG_MAX);
	info.time_to_eat = parse_arg_to_long(argv[3], LONG_MAX);
	info.time_to_sleep = parse_arg_to_long(argv[4], LONG_MAX);
	info.nr_times_to_eat = 0;
	if (argc == 6)
		info.nr_times_to_eat = parse_arg_to_long(argv[5], INT_MAX);
	if (info.nr_philos < 0 || info.time_to_die < 0 || info.time_to_eat < 0
		|| info.time_to_sleep < 0 || info.nr_times_to_eat < 0)
		return (EXIT_FAILURE);
	info.one_dead = 0;
	info.nr_fully_fed_philo = 0;
	printf("nr of philos = \t\t %i \n", info.nr_philos);
	printf("time to die = \t\t %li \n", info.time_to_die);
	printf("time to eat = \t\t %li \n", info.time_to_eat);
	printf("time to sleep = \t %li \n", info.time_to_sleep);
	printf("nr  times to eat = \t %i \n", info.nr_times_to_eat);
	return (0);
}
