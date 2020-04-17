/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 15:02:54 by hbrulin           #+#    #+#             */
/*   Updated: 2020/04/17 15:44:57 by hbrulin          ###   ########.fr       */
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
		//usleep(8 * 1000);
	}
	exit (0);
	return (NULL);
}

int		ft_wait(t_philo *philo, int nb)
{
	int status;
	int i;

	while (1)
	{
		status = 0;
		if (waitpid(-1, &status, 0) < 0 || WIFEXITED(status)) //si un process s'arrête, je kill tout le monde
		{
			i = -1;
			while (++i < nb)
				kill(philo[i].pid, SIGINT);
			exit(WEXITSTATUS(status));
		}
	}
}