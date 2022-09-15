/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mevan-de <mevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 11:20:16 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/09/15 15:20:40 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "../include/philo.h"

bool	is_done(t_info *info)
{
	return(info->done);
}
//grab forks and eat

//write msg (both main and philos)

//wait (sleep or think)
bool	wait_action(t_philo *philo, t_action ACTION)
{
	// MUTEX LOCK INFO 
	// check if not death message
	// get current time and create end time (start + wait_time_ms)
		//check action
			//send sleep or think message
	// MUTEX UNLOCK INFO
	// 
	// usleep for a bit and check 
	//
	long wait_start;
	int	wait_end;
	
	wait_start = get_elapsed_time(philo->info);
	pthread_mutex_lock(&philo->info->info_lock);
	pthread_mutex_lock(&philo->philo_lock);
	if(is_done(philo->info))
		return (false);
	wait_end = wait_start;
	if (ACTION == SLEEP)
		wait_end = wait_start + philo->info->time_to_sleep;
//	else if (ACTION == THINK)
//		wait_end = wait_start + ();
	pthread_mutex_unlock(&philo->philo_lock);
	pthread_mutex_unlock(&philo->info->info_lock);
	
	return (true);
}

void	*philosopher(void *data)
{
	t_philo	*philo;
	
	philo = (t_philo *)data;
	while (true)
	{
		pthread_mutex_lock(&philo->info->info_lock);
		if (is_done(philo->info))
		{
			pthread_mutex_unlock(&philo->info->info_lock);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->info->info_lock);
		usleep (250);
	}
	(void) data;
	return (NULL);
}