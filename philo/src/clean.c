/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 11:34:54 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/09/12 12:52:20 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	destroy_mutex_array(pthread_mutex_t *mutexes, int n)
{
	if (!mutexes)
		return ;
	while (n > 0)
	{
		n--;
		pthread_mutex_destroy(&mutexes[n]);
	}
}

void	free_info_contents(t_info *info)
{
	if (!info)
		return ;
	if (info->forks)
		free (info->forks);
	if (info->philos)
		free(info->philos);
}
