/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 15:02:54 by hbrulin           #+#    #+#             */
/*   Updated: 2020/04/16 16:55:43 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	end_sim(t_philo *philo)
{
	display(philo, DEAD);
	g_stop = 1;;
	exit(0);
}

void	*monitor_routine(void *philo_void)
{
	t_philo		*philo;
	unsigned long	time;

	philo = philo_void;
	while (!g_stop)
	{
		//pthread_mutex_lock(&philo->monitor->eating_mutexes[philo->id]);
		time = get_timestamp();
		if (time - philo->last_eat > philo->data->time_to_die)
			end_sim(philo);
		//pthread_mutex_unlock(&philo->monitor->eating_mutexes[philo->id]);
	}
	exit (0);
	return (NULL);
}

int		ft_monitor(t_philo *philo, int nb)
{
	int i;

	i = -1;
	while (++i < nb)
	{
		if (pthread_create(&philo[i].monitor_thread, NULL, &monitor_routine, &philo[i]) != 0)
			return(ft_error("Error: pthread create failed!\n"));
	}
	i = -1;
	while (++i < nb)
		pthread_join(philo[i].monitor_thread, NULL);
	i = -1;
	while (++i < nb)
		pthread_join(philo[i].thread, NULL);
	return (0);
}