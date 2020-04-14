/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 16:24:03 by hbrulin           #+#    #+#             */
/*   Updated: 2020/04/14 18:18:25 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h> //rm

/*void	*display(int id, int msg)


*/

void *routine(void *philo_v)
{
	t_philo		*philo;
	pthread_t	tid;

	philo = (t_philo*)philo_v;
	
	return ((void*)0);
}


int start_threading(t_data *data)
{
	int			i;
	pthread_t	th;
	void		*philo;

	while (i < data->number_of_philosophers)
	{
		philo = (void*)(&data->philos[i]);
		if (pthread_create(&th, NULL, &routine, philo) != 0)
			return (1);
		i++;
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_data data;

	if (argc < 5 || argc > 6)
		return (ft_error("error: bad arguments\n"));
	if (init_data(&data, argc, argv))
		return (free_data(&data) && ft_error("error: initializing\n"));
	if (start_threading(&data))
		return (free_data(&data) && exit_error("error: multithreading\n"));
	return (0);
}