/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 16:24:20 by hbrulin           #+#    #+#             */
/*   Updated: 2020/04/16 16:44:12 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

bool	g_stop;

typedef enum			e_status
{
	EATING,
	THINKING,
	SLEEPING,
	FORK_IN_USE,
	DEAD,
	DONE
}						t_status;

typedef struct s_data
{
	int nb_philo;
	unsigned long time_to_die;
	unsigned long time_to_eat;
	unsigned long time_to_sleep;
	int must_eat_nb;
	unsigned long start;
}				t_data;

typedef struct			s_monitor
{
	//bool				stop;
	pthread_mutex_t		stdout_mutex;
	pthread_mutex_t		*forks;
	//pthread_mutex_t		*eating_mutexes; //besoin de ça?
}						t_monitor;

typedef struct		s_philo
{
	int				id;
	t_data			*data;
	t_monitor		*monitor;
	unsigned long	last_eat;
	//bool				stopped;
	pthread_t			thread;
	pthread_t			monitor_thread; //besoin de ça?
}					t_philo;

unsigned long	get_timestamp(void);
int				ft_error(char *s);
int				init_data(t_data *data, int argc, char **argv);
void			ft_putstr(char *s);
void			ft_putnbr(unsigned long n);
int				ft_atoi(const char *str);
void			ft_bzero(void *s, size_t n);
int				init_monitor(t_data *data, t_monitor *monitor);
int				init_philos(t_data *data, t_monitor *monitor);
void			*ft_calloc(size_t len);
void			*routine(void *philo_void);
int				ft_monitor(t_philo *philo, int nb);
int				ft_putchar(char c);
void			display(const t_philo *philo, t_status status);


#endif