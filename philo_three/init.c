/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 17:03:17 by hbrulin           #+#    #+#             */
/*   Updated: 2020/05/07 18:43:05 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *monitor_count(t_data *data, t_monitor *monitor)
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
	sem_post(monitor->stdout_sem);
	exit (0);
}

int start_monitor_count(t_data *data, t_monitor *monitor)
{
	if (data->must_eat_nb > 0)
	{
		if (!(monitor->pid_count = fork()))
			monitor_count(data, monitor);
	}
	return (0);
}

int			open_sesame(sem_t **sem, char *name, int ressources)
{
	sem_unlink(name);
	*sem = sem_open(name, O_CREAT, 0666, ressources);
	if (!*sem || *sem == SEM_FAILED)
		return (ft_error("Error: semaphore not created\n"));
	return (0);
}

int			init_philos(t_data *data, t_monitor *monitor)
{
	t_philo		*philo;
	int			i;

	if (!(philo = ft_calloc(sizeof(t_philo) * data->nb_philo)))
		return (ft_error("Error: malloc fail\n"));
	if (!(monitor->eat_count_m = ft_calloc(sizeof(sem_t *) * data->nb_philo)))
		return (1);
	i = -1;
	while (++i < data->nb_philo)
	{
		philo[i] = (t_philo) { .id = i, .data = data, .monitor = monitor,
			.last_eat = data->start };
		if (open_sesame(&monitor->eat_count_m[i], monitor->names_eat_max[i], 0))
			return (1);
		if (!(philo[i].pid = fork()))
			routine(&philo[i]);
		usleep(10);
	}
	start_monitor_count(data, monitor);
	ft_wait(philo, data->nb_philo);
	free(philo);
	return (0);
}

int			init_monitor(t_data *data, t_monitor *monitor)
{
	int i;

	if (open_sesame(&monitor->forks, S_FORKS, data->nb_philo) ||
		open_sesame(&monitor->stdout_sem, S_STDOUT, 1))
		return (1);
	if (!(monitor->is_eating = ft_calloc(sizeof(sem_t *) * data->nb_philo)))
		return (1);
	i = -1;
	while (++i < data->nb_philo)
	{
		if (open_sesame(&monitor->is_eating[i], monitor->names[i], 1))
			return (1);
	}
	return (0);
}

int			check_value(char *s)
{
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (1);
		s++;
	}
	return (0);
}

int			init_data(t_data *data, int argc, char **argv)
{
	int i;

	i = 1;
	while (argv[i])
	{
		if (check_value(argv[i]))
			return (1);
		i++;
	}
	if ((data->nb_philo = ft_atoi(argv[1])) < 1)
		return (1);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->must_eat_nb = ft_atoi(argv[5]);
	else
		data->must_eat_nb = 0;
	data->start = get_timestamp();
	return (0);
}
