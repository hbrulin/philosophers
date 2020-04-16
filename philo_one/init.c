/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 17:03:17 by hbrulin           #+#    #+#             */
/*   Updated: 2020/04/16 16:33:52 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		init_philos(t_data *data, t_monitor *monitor)
{
	t_philo		*philo;
	int			i;

	if (!(philo = ft_calloc(sizeof(t_philo) * data->nb_philo)))
		return (ft_error("Error: malloc fail\n"));
	i = -1;
	while (++i < data->nb_philo)
	{
		philo[i] = (t_philo) { .id = i, .data = data, .monitor = monitor,
			.last_eat = data->start };
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]) != 0)
			return(ft_error("Error: thread initialization failed!\n"));
		usleep(10);
	}
	if (ft_monitor(philo, data->nb_philo))
		return (1);
	free(philo);
	return (0);
}

int	init_monitor(t_data *data, t_monitor *monitor)
{
	int i;

	if (!(monitor->forks = ft_calloc(sizeof(pthread_mutex_t) * data->nb_philo)))
		return (ft_error("Error: malloc fail\n"));
	/*if (!(monitor->eating_mutexes = ft_calloc(sizeof(pthread_mutex_t) * data->nb_philo)))
		return (ft_error("Error: malloc fail\n"));*/
	if (pthread_mutex_init(&monitor->stdout_mutex, NULL) != 0) 
		return(ft_error("Error: mutex initialization failed!\n"));
	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_mutex_init(&monitor->forks[i], NULL) != 0) //protection mutex fourchettes
			return(ft_error("Error: mutex initialization failed!\n"));
	}
	i = -1;
	/*while (++i < data->nb_philo)
	{
		if (pthread_mutex_init(&monitor->eating_mutexes[i], NULL) != 0) 
			return(ft_error("Error: mutex initialization failed!\n"));
	}*/
	return (0);
}

int		init_data(t_data *data, int argc, char **argv)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->must_eat_nb = ft_atoi(argv[5]);
	else
		data->must_eat_nb = 0;
	if (data->nb_philo < 1 || data->must_eat_nb < 0) //autres cas? pour les autres pas possibles car unsigned long
		return (1);
	data->start = get_timestamp();
	return (0);
}