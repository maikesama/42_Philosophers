/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaci <mpaci@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 12:17:15 by mpaci             #+#    #+#             */
/*   Updated: 2021/12/14 14:07:55 by mpaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_routine_starter(t_philo *philo, t_all *all)
{
	int	i;

	i = 0;
	if (philo->all->np == 1)
	{
		gettimeofday(&philo->all->time, NULL);
		ft_state(FORK, philo);
		ft_timer_ms(philo, philo->all->ttd);
		ft_state(DEAD, philo);
	}
	else
	{
		gettimeofday(&philo->all->time, NULL);
		while (i < all->np)
		{
			usleep(10);
			pthread_create(&philo[i].philo, NULL,
				(void *)routine, &philo[i]);
			i++;
		}
	}
}

void	ft_wait_for_threads(t_philo *philo, t_all *all)
{
	int	i;

	i = 0;
	while (i < all->np)
	{
		if (philo->all->np == 1)
		{
			pthread_join(philo[i].death, NULL);
			pthread_detach(philo[i].philo);
		}
		pthread_join(philo[i].philo, NULL);
		i++;
	}
	free(philo);
	free(philo->all->forks);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_all	all;

	philo = NULL;
	if (!init(&all, argv, argc))
		return (0);
	philo = malloc(sizeof(*philo) * all.np);
	init_philo(philo, &all);
	ft_routine_starter(philo, &all);
	ft_wait_for_threads(philo, &all);
}
