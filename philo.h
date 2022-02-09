/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaci <mpaci@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 12:17:21 by mpaci             #+#    #+#             */
/*   Updated: 2021/12/14 13:07:47 by mpaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

enum e_state {
	DEAD,
	FORK,
	EAT,
	SLEEP,
	THINK,
};

static const char *const	g_status_str[] = {
	"\e[31mis DEAD\e[0m",
	"\e[33mhas taken a fork\e[0m",
	"\e[32mis eating\e[0m",
	"\e[35mis sleeping\e[0m",
	"\e[34mis thinking\e[0m",
};

typedef struct s_all
{
	int				np;
	int				ttd;
	int				tts;
	int				tte;
	int				ntte;
	int				simulation;
	struct timeval	time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	dead;
	pthread_mutex_t	mutex_stamp;
}				t_all;

typedef struct s_philo
{
	int				eaten;
	int				pid;
	int				need_eat;
	pthread_t		philo;
	pthread_t		death;
	t_all			*all;
	struct timeval	eat;
}				t_philo;

int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		check(int argc, char **argv);
int		init(t_all *all, char **argv, int argc);
void	init_philo(t_philo *philo, t_all *all);
void	ft_state(int state, t_philo *philo);
void	ft_timer_ms(t_philo *philo, long int dealy);
int		ft_time_elapsed_ms(struct timeval t0, struct timeval t1);
void	routine(t_philo *philo);

#endif