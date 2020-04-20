/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lib_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 17:17:58 by hbrulin           #+#    #+#             */
/*   Updated: 2020/04/20 17:16:26 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		ft_neg(int ctr, const char *str)
{
	if (str[ctr] == '-')
		return (-1);
	else
		return (1);
}

int		ft_atoi(const char *str)
{
	int nbr;
	int ctr;
	int neg;

	ctr = 0;
	nbr = 0;
	neg = 1;
	while (str[ctr] == ' ' || str[ctr] == '\n' || str[ctr] == '\r' ||
			str[ctr] == '\v' || str[ctr] == '\t' || str[ctr] == '\f')
		ctr++;
	if (str[ctr] == '+' || str[ctr] == '-')
	{
		neg = ft_neg(ctr, str);
		ctr++;
	}
	while (str[ctr] >= '0' && str[ctr] <= '9')
	{
		nbr = nbr * 10 + str[ctr] - '0';
		ctr++;
	}
	return (nbr * neg);
}

void	ft_tabdel(void **tab)
{
	int i;

	i = 0;
	if (tab)
	{
		while (tab[i])
			free(tab[i++]);
		free(tab);
	}
}
