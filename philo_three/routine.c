/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 15:02:01 by hbrulin           #+#    #+#             */
/*   Updated: 2020/05/07 18:42:21 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	display(const t_philo *philo, t_status status)
{
	sem_wait(philo->monitor->stdout_sem);
	if (g_stop)
		return ;
	ft_putnbr(get_timestamp());
	ft_putchar(' ');
	ft_putnbr(philo->id + 1);
	if (status == EATING)
		ft_putstr(" is eating\n");
	else if (status == THINKING)
		ft_putstr(" is thinking\n");
	else if (status == SLEEPING)
		ft_putstr(" is sleeping\n");
	else if (status == FORK_IN_USE)
		ft_putstr(" has taken a fork\n");
	else if (status == DEAD)
	{
		ft_putstr(" died");
		return ;
	}
	sem_post(philo->monitor->stdout_sem);
}

void	eat(t_philo *philo)
{
	sem_wait(philo->monitor->order);
	sem_wait(philo->monitor->forks);
	display(philo, FORK_IN_USE);
	sem_wait(philo->monitor->forks);
	display(philo, FORK_IN_USE);
	sem_post(philo->monitor->order);
	display(philo, EATING);
	sem_wait(philo->monitor->is_eating[philo->id]);
	philo->last_eat = get_timestamp();
	usleep(philo->data->time_to_eat * 1000);
	sem_post(philo->monitor->forks);
	sem_post(philo->monitor->forks);
	sem_post(philo->monitor->is_eating[philo->id]);
	sem_post(philo->monitor->eat_count_m[philo->id]);
}

int		routine(t_philo *philo)
{
	int			i;
	int			total;

	i = 0;
	total = 0;
	usleep(1);
	if (pthread_create(&philo[i].monitor_thread, NULL,
		&monitor_routine, &philo[i]) != 0)
		return (ft_error("Error: pthread create failed!\n"));
	while (1)
	{
		eat(philo);
		total++;
		if (total == philo->data->must_eat_nb && philo->data->must_eat_nb != 0)
		{
			while (1)
				;
		}
		display(philo, SLEEPING);
		usleep(philo->data->time_to_sleep * 1000);
		display(philo, THINKING);
	}
	return (0);
}
