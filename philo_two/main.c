/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 16:24:03 by hbrulin           #+#    #+#             */
/*   Updated: 2020/04/20 17:08:57 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	g_stop = 0;

int		main(int argc, char **argv)
{
	t_data		data;
	t_monitor	monitor;

	ft_bzero(&data, sizeof(t_data));
	ft_bzero(&monitor, sizeof(t_monitor));
	if (argc < 5 || argc > 6)
		return (ft_error("error: bad arguments\n"));
	if (init_data(&data, argc, argv))
		return (ft_error("error: bad arguments\n"));
	if (init_names(&data, &monitor))
		return (ft_error("error: init fail\n"));
	if (init_monitor(&data, &monitor) || init_philos(&data, &monitor))
	{
		free_monitor(&data, &monitor);
		return (1);
	}
	free_monitor(&data, &monitor);
	return (0);
}
