/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 15:02:01 by hbrulin           #+#    #+#             */
/*   Updated: 2020/04/20 17:13:51 by hbrulin          ###   ########.fr       */
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
	else if (status == DONE)
		ft_putstr(" has eaten enough\n");
	else if (status == DEAD)
		ft_putstr(" died\n");
	sem_post(philo->monitor->stdout_sem);
}

void	eat(t_philo *philo)
{
	sem_wait(philo->monitor->forks);
	display(philo, FORK_IN_USE);
	sem_wait(philo->monitor->forks);
	display(philo, FORK_IN_USE);
	display(philo, EATING);
	sem_wait(philo->monitor->is_eating[philo->id]);
	philo->last_eat = get_timestamp();
	usleep(philo->data->time_to_eat * 1000);
	sem_post(philo->monitor->forks);
	sem_post(philo->monitor->forks);
	sem_post(philo->monitor->is_eating[philo->id]);
}

void	*routine(void *philo_void)
{
	t_philo		*philo;
	int			i;

	philo = philo_void;
	i = 0;
	while (1)
	{
		eat(philo);
		if (++i >= philo->data->must_eat_nb && philo->data->must_eat_nb != 0)
		{
			display(philo, DONE);
			g_stop = 1;
			usleep(8 * 1000);
			break ;
		}
		display(philo, THINKING);
		display(philo, SLEEPING);
		usleep(philo->data->time_to_sleep * 1000);
	}
	return (NULL);
}
