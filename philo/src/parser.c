/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/08 15:10:52 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/09/26 10:31:28 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../include/philo.h"

long	parse_arg_to_long(char *argv, long max)
{
	long long	count;

	count = 0;
	if (!*argv)
		return (-1);
	while (*argv >= '0' && *argv <= '9')
	{
		count = count * 10 + (*argv - '0');
		if (count > max)
			return (-1);
		argv++;
	}
	if (*argv != '\0')
		return (-1);
	return (count);
}

bool	parse_input_to_info(int argc, char **argv, t_info *info)
{
	if (!info)
		return (false);
	info->nr_philos = parse_arg_to_long(argv[1], INT_MAX);
	info->time_to_die = parse_arg_to_long(argv[2], INT_MAX);
	info->time_to_eat = parse_arg_to_long(argv[3], INT_MAX);
	info->time_to_sleep = parse_arg_to_long(argv[4], INT_MAX);
	info->nr_times_to_eat = -1;
	if (argc == 6)
		info->nr_times_to_eat = parse_arg_to_long(argv[5], INT_MAX);
	if (info->nr_philos <= 0 || info->time_to_die < 0 || info->time_to_eat < 0
		|| info->time_to_sleep < 0
		|| (argc == 6 && info->nr_times_to_eat < 0))
		return (false);
	return (true);
}
