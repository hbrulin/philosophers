/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 16:24:20 by hbrulin           #+#    #+#             */
/*   Updated: 2020/04/14 17:30:36 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

# define NOTHING 0
# define EAT 	1
# define SLEEP  2
# define THINK	3
# define DIED 	4

typedef struct		s_philo
{
	int				id;
	int				eat_count;
	int				state;
	int				rfork; //id fourchette
	int				lfork;
}					t_philo;

typedef struct s_data
{
	int number_of_philosophers;
	unsigned long time_to_die;
	unsigned long time_to_eat;
	unsigned long time_to_sleep;
	int must_eat_nb;
	unsigned long start;
	t_philo			*philos;
}				t_data;

unsigned long	get_timestamp(void);
int				ft_error(char *s);
int		init_data(t_data *data, int argc, char **argv);
void	ft_putstr(char *s);
void	ft_putnbr(unsigned long n);
int	ft_atoi(const char *str);


#endif