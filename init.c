/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaci <mpaci@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 12:17:04 by mpaci             #+#    #+#             */
/*   Updated: 2021/12/09 12:42:07 by mpaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
	{
		printf("wrong amount of arguments\n");
		return (0);
	}
	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				printf("wrong parameters\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	init(t_all *all, char **argv, int argc)
{
	if (!check(argc, argv))
		return (0);
	all->np = ft_atoi(argv[1]);
	if (all->np <= 0)
	{
		printf("Come with some philosophers, we made spaghetti\n");
		return (0);
	}
	all->ttd = ft_atoi(argv[2]);
	all->tte = ft_atoi(argv[3]);
	all->tts = ft_atoi(argv[4]);
	all->simulation = 1;
	if (argc == 6)
		all->ntte = ft_atoi(argv[5]);
	else
		all->ntte = -1;
	all->forks = malloc(sizeof(*all->forks) * all->np);
	return (1);
}

void	init_philo(t_philo *philo, t_all *all)
{
	int	i;

	i = 0;
	while (i < all->np)
	{
		philo[i].pid = i;
		philo[i].eaten = 0;
		philo[i].need_eat = 0;
		philo[i].all = all;
		pthread_mutex_init(&all->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&all->mutex_stamp, NULL);
	pthread_mutex_init(&all->dead, NULL);
}
