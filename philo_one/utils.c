/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 16:24:11 by hbrulin           #+#    #+#             */
/*   Updated: 2020/04/14 18:00:52 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		free_data(t_data *data)
{
	if (data->philos)
		free(data->philos);
	//destroy mutexes
	return (1);
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