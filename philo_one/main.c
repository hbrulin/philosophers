/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 16:24:03 by hbrulin           #+#    #+#             */
/*   Updated: 2020/04/14 17:15:42 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h> //rm

/*void	*display(int id)


*/

int main(int argc, char **argv)
{
	t_data data;

	if (argc < 5 || argc > 6)
		return (ft_error("error: bad arguments\n"));
	if (init_data(&data, argc, argv))
		return (ft_error("error: bad arguments"));
	return (0);
}