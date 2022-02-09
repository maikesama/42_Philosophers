/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaci <mpaci@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 13:53:15 by mpaci             #+#    #+#             */
/*   Updated: 2021/12/14 14:07:24 by mpaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_dead(t_philo *philo)
{
	struct timeval	timenow;

	while (philo->all->simulation && philo->all->ttd
		&& philo->eaten != philo->all->ntte)
	{
		gettimeofday(&timenow, NULL);
		usleep(50);
		pthread_mutex_lock(&philo->all->dead);
		if (ft_time_elapsed_ms(philo->eat, timenow) > philo->all->ttd
			&& philo->all->simulation)
		{
			ft_state(DEAD, philo);
			philo->all->simulation = 0;
		}
		pthread_mutex_unlock(&philo->all->dead);
	}
}

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->forks[philo->pid]);
	if (philo->pid == philo->all->np - 1)
		pthread_mutex_lock(&philo->all->forks[0]);
	else
		pthread_mutex_lock(&philo->all->forks[philo->pid + 1]);
}

void	untake_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->all->forks[philo->pid]);
	if (philo->pid == philo->all->np - 1)
		pthread_mutex_unlock(&philo->all->forks[0]);
	else
		pthread_mutex_unlock(&philo->all->forks[philo->pid + 1]);
}

void	routine(t_philo *philo)
{
	gettimeofday(&philo->eat, NULL);
	pthread_create(&philo->death, NULL, (void *)is_dead, philo);
	while (philo->all->simulation == 1 && philo->eaten != philo->all->ntte
		&& philo->all->simulation)
	{
		take_fork(philo);
		ft_state(FORK, philo);
		ft_state(EAT, philo);
		philo->eaten++;
		gettimeofday(&philo->eat, NULL);
		ft_timer_ms(philo, philo->all->tte);
		untake_fork(philo);
		if (philo->eaten == philo->all->ntte)
			break ;
		ft_state(SLEEP, philo);
		ft_timer_ms(philo, philo->all->tts);
		ft_state(THINK, philo);
	}
	pthread_join(philo->death, NULL);
}
