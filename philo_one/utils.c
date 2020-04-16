/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 16:24:11 by hbrulin           #+#    #+#             */
/*   Updated: 2020/04/16 18:06:06 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_monitor(t_data *data, t_monitor *monitor)
{
	int i;

	i = 0;
	while (i < data->nb_philo)
		pthread_mutex_destroy(&monitor->forks[i++]);
	i = 0;
	pthread_mutex_destroy(&monitor->stdout_mutex);
	if (monitor->forks)
		free(monitor->forks);
}

void	*ft_calloc(size_t len)
{
	void	*str;

	if (!(str = malloc(len)))
		return (NULL);
	ft_bzero(str, len);
	return (str);
}

int				ft_error(char *s)
{
	ft_putstr(s);
	return (1);
}

unsigned long	get_timestamp(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_usec / 1000 + tv.tv_sec * 1000); //(secondes et microsecondes)
}