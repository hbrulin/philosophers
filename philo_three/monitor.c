/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 15:02:54 by hbrulin           #+#    #+#             */
/*   Updated: 2020/05/07 18:39:07 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_count(t_data *data, t_monitor *monitor)
{
	int		total;
	int		i;

	total = 0;
	while (total < data->must_eat_nb)
	{
		i = 0;
		while (i < data->nb_philo)
			sem_wait(monitor->eat_count_m[i++]);
		total++;
	}
	sem_wait(monitor->stdout_sem);
	ft_putnbr(get_timestamp());
	ft_putstr(" Philosophers have eaten enough\n");
	exit(0);
}

int		start_monitor_count(t_data *data, t_monitor *monitor)
{
	if (data->must_eat_nb > 0)
	{
		if (!(monitor->pid_count = fork()))
			monitor_count(data, monitor);
	}
	return (0);
}

void	*monitor_routine(void *philo_void)
{
	t_philo			*philo;
	unsigned long	time;

	philo = philo_void;
	while (!g_stop)
	{
		sem_wait(philo->monitor->is_eating[philo->id]);
		time = get_timestamp();
		if (time - philo->last_eat > philo->data->time_to_die)
		{
			display(philo, DEAD);
			g_stop = 1;
			exit(0);
		}
		sem_post(philo->monitor->is_eating[philo->id]);
		usleep(8 * 1000);
	}
	exit(0);
	return (NULL);
}

int		ft_wait(t_philo *philo, int nb)
{
	int status;
	int i;

	while (1)
	{
		status = 0;
		if (waitpid(-1, &status, 0) < 0 || WIFEXITED(status))
		{
			i = -1;
			while (++i < nb)
				kill(philo[i].pid, SIGINT);
			kill(philo->monitor->pid_count, SIGINT);
			return (0);
		}
	}
	return (0);
}
