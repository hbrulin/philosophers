/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 15:02:01 by hbrulin           #+#    #+#             */
/*   Updated: 2020/04/16 16:42:30 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	display(const t_philo *philo, t_status status)
{
	pthread_mutex_lock(&philo->monitor->stdout_mutex);
	if (g_stop)
		return;
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
	pthread_mutex_unlock(&philo->monitor->stdout_mutex);
}


void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->monitor->forks[philo->id]);
	display(philo, FORK_IN_USE);
	pthread_mutex_lock(&philo->monitor->forks[(philo->id + 1) % philo->data->nb_philo]);
	display(philo, FORK_IN_USE);
	display(philo, EATING);
	//pthread_mutex_lock(&philo->monitor->eating_mutexes[philo->id]); //besoin de ça?
	philo->last_eat = get_timestamp();
	usleep(philo->data->time_to_eat * 1000); 
	pthread_mutex_unlock(&philo->monitor->forks[philo->id]);
	pthread_mutex_unlock(&philo->monitor->forks[(philo->id + 1) % philo->data->nb_philo]);
	//pthread_mutex_unlock(&philo->monitor->eating_mutexes[philo->id]);
}

void	*routine(void *philo_void)
{
	t_philo	*philo;
	int			i;

	philo = philo_void;
	i = 0;
	while (1)
	{
		eat(philo); //il mange avant de penser
		if (++i >= philo->data->must_eat_nb)
			break;
		display(philo, THINKING);
		display(philo, SLEEPING);
		usleep(philo->data->time_to_sleep * 1000);
	}
	display(philo, DONE);
	g_stop = 1;
	return (NULL);
}