/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 16:24:11 by hbrulin           #+#    #+#             */
/*   Updated: 2020/04/20 14:38:36 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_monitor(t_data *data, t_monitor *monitor)
{
	int i;
	(void) data;
	//(void)monitor;
	sem_close(monitor->forks);
	i = -1;
	/*while (++i < data->nb_philo)
		sem_close(monitor->is_eating[i]);*/
	free(monitor->is_eating);
	//sem_close(monitor->stdout_sem);
	return ;
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