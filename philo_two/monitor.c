/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 15:02:54 by hbrulin           #+#    #+#             */
/*   Updated: 2020/04/17 15:00:05 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_routine(void *philo_void)
{
	t_philo		*philo;
	unsigned long	time;

	philo = philo_void;
	while (!g_stop)
	{
		time = get_timestamp();
		if (time - philo->last_eat > philo->data->time_to_die)
		{
			display(philo, DEAD);
			g_stop = 1;
		}
		usleep(8 * 1000);
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