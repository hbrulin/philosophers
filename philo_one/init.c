/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 17:03:17 by hbrulin           #+#    #+#             */
/*   Updated: 2020/04/14 17:29:50 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		data->philos[i].id = i;
		data->philos[i].eat_count = 0;
		data->philos[i].state = NOTHING;
		data->philos[i].lfork = i;
		data->philos[i].rfork = (i + 1) % data->number_of_philosophers;
		i++;
	}
}


int		init_data(t_data *data, int argc, char **argv)
{
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->must_eat_nb = ft_atoi(argv[5]);
	else
		data->must_eat_nb = 0;
	if (data->number_of_philosophers < 2 || data->must_eat_nb < 0) //autres cas?
		return (1);
	data->start = get_timestamp();
	if (!(data->philos =
		(t_philo*)malloc(sizeof(*(data->philos)) * data->number_of_philosophers)))
		return (1);
	init_philos(data);
	return (0);
}