/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msulc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 09:25:52 by msulc             #+#    #+#             */
/*   Updated: 2023/09/22 09:25:54 by msulc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	input_controll(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (printf("Wrong number of arguments\n"), 1);
	if (ft_looking_for_characters(argv))
		return (printf("Error: wrong input\n"), 1);
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) <= 0
		|| ft_atoi(argv[3]) <= 0 || ft_atoi(argv[4]) <= 0)
		return (printf("All arguments need to be greater than zero\n"), 1);
	return (0);
}

void	init_one(t_philo *philo, t_data *data)
{
	philo = init_philos(1, data);
	pthread_create(&(data->thread[0]), NULL, &lets_live_short, (void *) philo);
}

void	*life_guard(void *the_data)
{
	t_data	*data;
	int		i;

	data = (t_data *)the_data;
	i = 0;
	while (1 && data->live_status == 1 && data->philos[i].m_eaten < data->m2eat)
	{
		while (i < data->num_philos)
		{
			if ((set_the_time() - data->philos[i].eaten_last) >= data->t2die
				&& data->philos[i].status == 0)
			{
				message(&data->philos[i], DEAD);
				data->live_status = 0;
				return (NULL);
			}
			i++;
			usleep(100);
		}
		i = 0;
	}
	return (NULL);
}

void	message(t_philo *philo, char *state)
{
	if (philo->data->live_status == 1)
	{
		pthread_mutex_lock(&philo->data->report);
		printf("%lu %i %s\n", get_the_time(philo->data->start_time), \
			philo->p_nbr, state);
		pthread_mutex_unlock(&philo->data->report);
	}
	return ;
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork[1]);
	pthread_mutex_unlock(philo->fork[0]);
}
