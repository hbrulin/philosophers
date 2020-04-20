/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_names.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 17:05:24 by hbrulin           #+#    #+#             */
/*   Updated: 2020/04/20 17:05:57 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char		*create_name(void)
{
	char		*ret;
	size_t		i;
	static char *alpha = "abcdefghijklmopqrstuvxyz";

	if (!(ret = malloc(sizeof(char) * 4)))
		return (NULL);
	i = 0;
	while (i <= 2)
	{
		ret[i] = alpha[get_timestamp() % 26];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

int			init_names(t_data *data, t_monitor *monitor)
{
	int i;

	i = 0;
	if (!(monitor->names = malloc(sizeof(char *) * data->nb_philo + 1)))
		return (1);
	while (i < data->nb_philo)
	{
		monitor->names[i] = create_name();
		i++;
	}
	monitor->names[i] = NULL;
	return (0);
}
