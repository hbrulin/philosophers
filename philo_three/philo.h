/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 16:24:20 by hbrulin           #+#    #+#             */
/*   Updated: 2020/05/07 18:36:34 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

# define S_FORKS "sem_forks"
# define S_STDOUT "sem_stdout"

bool					g_stop;

typedef enum			e_status
{
	EATING,
	THINKING,
	SLEEPING,
	FORK_IN_USE,
	DEAD,
	DONE
}						t_status;

typedef struct			s_data
{
	int					nb_philo;
	unsigned long		time_to_die;
	unsigned long		time_to_eat;
	unsigned long		time_to_sleep;
	int					must_eat_nb;
	unsigned long		start;
}						t_data;

typedef struct			s_monitor
{
	sem_t				*forks;
	sem_t				*order;
	sem_t				*stdout_sem;
	sem_t				**is_eating;
	char				**names;
	char				**names_eat_max;
	sem_t				**eat_count_m;
	pid_t				pid_count;
}						t_monitor;

typedef struct			s_philo
{
	int					id;
	t_data				*data;
	t_monitor			*monitor;
	unsigned long		last_eat;
	pid_t				pid;
	pthread_t			monitor_thread;
}						t_philo;

unsigned long			get_timestamp(void);
int						ft_error(char *s);
int						init_data(t_data *data, int argc, char **argv);
void					ft_putstr(char *s);
void					ft_putnbr(unsigned long n);
int						ft_atoi(const char *str);
void					ft_bzero(void *s, size_t n);
int						init_monitor(t_data *data, t_monitor *monitor);
int						init_philos(t_data *data, t_monitor *monitor);
void					*ft_calloc(size_t len);
int						routine(t_philo	*philo);
int						ft_wait(t_philo *philo, int nb);
int						ft_putchar(char c);
void					display(const t_philo *philo, t_status status);
void					free_monitor(t_data *data, t_monitor *monitor);
void					*monitor_routine(void *philo_void);
void					ft_tabdel(void **tab);
int						init_names(t_data *data, t_monitor *monitor);
int						init_max_names(t_data *data, t_monitor *monitor);
int						start_monitor_count(t_data *data, t_monitor *monitor);

#endif
