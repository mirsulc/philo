/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msulc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 09:39:54 by msulc             #+#    #+#             */
/*   Updated: 2023/09/19 09:40:00 by msulc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_data	*data;
	t_philo	*philo;
	int		i;

	i = -1;
	if (input_controll(argc, argv))
		return (1);
	data = fill_data(argc, argv);
	data->start_time = set_the_time();
	if (ft_atoi(argv[1]) == 1)
		init_one(philo, data);
	else
	{
		while (++i < data->num_philos)
		{
			philo = init_philos(i + 1, data);
			pthread_create(&(data->thread[i]), NULL, \
				&lets_live, (void *) philo);
		}
	}
	pthread_create(&data->guard, NULL, &life_guard, (void *) data);
	threads_join(data);
	return (cleaning(data), 0);
}

t_data	*fill_data(int argc, char **argv)
{
	t_data	*data;
	int		i;

	i = -1;
	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->num_philos = ft_atoi(argv[1]);
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	data->thread = malloc(sizeof(pthread_t) * data->num_philos);
	data->forky = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->philos || !data->thread || !data->forky)
		return (NULL);
	while (++i < data->num_philos)
		pthread_mutex_init(&data->forky[i], NULL);
	data->t2die = ft_atoi(argv[2]);
	data->t2eat = ft_atoi(argv[3]);
	data->t2sleep = ft_atoi(argv[4]);
	if (argc == 6 && ft_atoi(argv[5]) > 0)
		data->m2eat = ft_atoi(argv[5]);
	else
		data->m2eat = 1000000000;
	data->live_status = 1;
	pthread_mutex_init(&data->report, NULL);
	return (data);
}

t_philo	*init_philos(int i, t_data *data)
{
	t_philo	*philo;

	philo = &data->philos[i - 1];
	philo->data = data;
	philo->p_nbr = i;
	philo->m_eaten = 0;
	philo->eaten_last = set_the_time();
	philo->status = 0;
	return (philo);
}

void	threads_join(t_data *data)
{
	t_philo	*philo;
	int		i;

	philo = data->philos;
	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->thread[i], NULL);
		i++;
	}
}

void	cleaning(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
	{
		if (data->forky)
			pthread_mutex_destroy(&data->forky[i]);
	}
	free(data->thread);
	free(data->philos);
	free(data->forky);
	pthread_mutex_destroy(&data->report);
	pthread_join(data->guard, NULL);
	free(data);
}
