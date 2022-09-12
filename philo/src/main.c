/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 17:03:08 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/09/12 11:00:57 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_info	info;

	if(argc < 5 || argc > 6)
		return (1);
	if (!parse_input_to_info(argc, argv, &info))
		return (EXIT_FAILURE);
	info.one_dead = 0;
	info.nr_fully_fed_philo = 0;
	if(!init_forks(&info))
		return (EXIT_FAILURE);
	if(!init_philos(&info))
		return (EXIT_FAILURE);
	int i;
	for (i = 0; i < info.nr_philos; ++i){
		printf("philo fork id left: %i\n", info.philos[i].fork_id1);
		printf("philo fork id right: %i\n", info.philos[i].fork_id2);
	}
	return (0);
}
