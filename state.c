/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaci <mpaci@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 12:46:15 by mpaci             #+#    #+#             */
/*   Updated: 2021/12/09 13:18:06 by mpaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_time_elapsed_ms(struct timeval t0, struct timeval t1)
{
	int	elapsed;

	elapsed = (int)(t1.tv_sec - t0.tv_sec) *(1000.0);
	elapsed += (int)(t1.tv_usec - t0.tv_usec) / 1000.0;
	return (elapsed);
}

void	ft_state(int state, t_philo *philo)
{
	struct timeval	timenow;
	int				elapsed;

	gettimeofday(&timenow, NULL);
	pthread_mutex_lock(&philo->all->mutex_stamp);
	elapsed = ft_time_elapsed_ms(philo->all->time, timenow);
	if (elapsed != 0)
		elapsed += 1;
	if (philo->all->simulation)
		printf("%d\tphilo %d %s\n",
			elapsed, philo->pid + 1, g_status_str[state]);
	pthread_mutex_unlock(&philo->all->mutex_stamp);
}

void	ft_timer_ms(t_philo *philo, long int delay)
{
	struct timeval	time;
	int				goal;

	gettimeofday(&time, NULL);
	goal = (int)(time.tv_sec * 1000 + time.tv_usec / 1000 + delay);
	while (goal > (int)(time.tv_sec * 1000 + time.tv_usec / 1000)
			&& philo->all->simulation)
	{
		usleep (10);
		gettimeofday(&time, NULL);
	}
}
