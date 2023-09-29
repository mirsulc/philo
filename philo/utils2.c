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

//	kontrola vstupnich argumentu
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

//	inicializace programu/threadu filozofa v pripade, ze je zadan pouze jeden filozof
void	init_one(t_philo *philo, t_data *data)
{
	philo = init_philos(1, data);
	pthread_create(&(data->thread[0]), NULL, &lets_live_short, (void *) philo);
}

//	funkce, ktera kontroluje, zda filozofe neeprekrocili cas urceny k zivout - t2die
void	*life_guard(void *the_data)
{
	t_data	*data;
	int		i;

	data = (t_data *)the_data;
	i = 0;
//	zatimco jsou nazivu a pocet snedenych jidel je mensi nez pocet jidel, ktera maji snist
	while (1 && data->live_status == 1 && data->philos[i].m_eaten < data->m2eat)
	{
//	kontrola kazdeho jednoho filozofa
		while (i < data->num_philos)
		{
//	kontyrola casu po ktery mohou zit - aktualni cas minus cas posledniho jidla + zda prave nejedi
			if ((set_the_time() - data->philos[i].eaten_last) >= data->t2die
				&& data->philos[i].status == 0)
			{
//	vytisteni zpravy, ze filozof zemrel a zena zivotniho statusu
				message(&data->philos[i], DEAD);
				data->live_status = 0;
				return (NULL);
			}
			i++;
//	male zpozdeni pro usnadneni prace procesoru
			usleep(100);
		}
		i = 0;
	}
	return (NULL);
}

void	message(t_philo *philo, char *state)
{
//	vsechna hlaseni se vytisknou pouze pokud je zivotni status pozitivni
	if (philo->data->live_status == 1)
	{
//	uzamknuti mutexu na vypis hlaseni stavu
		pthread_mutex_lock(&philo->data->report);
		printf("%lu %i %s\n", get_the_time(philo->data->start_time), \
			philo->p_nbr, state);
		pthread_mutex_unlock(&philo->data->report);
	}
	return ;
}

//	funkce ktera odemyka obe vidlicky
void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork[1]);
	pthread_mutex_unlock(philo->fork[0]);
}
