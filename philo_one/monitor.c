/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 15:02:54 by hbrulin           #+#    #+#             */
/*   Updated: 2020/04/16 15:48:48 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	end_sim(t_philo *philo)
{
	display(philo, DEAD);
	philo->stopped = true;
	exit(0);
}

void	*monitor_routine(void *philo_void)
{
	t_philo		*philo;
	unsigned long	time;

	philo = philo_void;
	while (!philo->stopped)
	{
		pthread_mutex_lock(&philo->monitor->eating_mutexes[philo->id]);
		time = get_timestamp();
		if (time - philo->last_eat >
				(unsigned long)philo->data->time_to_die)
			end_sim(philo);
		pthread_mutex_unlock(&philo->monitor->eating_mutexes[philo->id]);
		//usleep(8 * 1000);
	}
	return (NULL);
}

int		ft_monitor(t_philo *philo, int nb)
{
	int i;

	i = -1;
	while (++i < nb)
	{
		if (pthread_create(&philo[i].monitor_thread, NULL, &monitor_routine, &philo[i]) != 0) //besoin de monitor_threads?
			return(ft_error("Error: pthread create failed!\n"));
	}
	i = -1;
	while (++i < nb)
		pthread_join(philo[i].monitor_thread, NULL); //besoin de ça?
	i = -1;
	while (++i < nb)
		pthread_join(philo[i].thread, NULL);
	return (0);
}