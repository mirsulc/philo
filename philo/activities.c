/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msulc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 09:47:36 by msulc             #+#    #+#             */
/*   Updated: 2023/09/27 09:47:40 by msulc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//	zde pridelujeme pointerum na vidlicky konkretni vidlicky na ktere maji ukazovat
//	vzdy 2 pro kazdeho filozofa. Take vytvarime loop, ve kterem se budou filozofove pohybovat
void	*lets_live(void *phhill)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *) phhill;
	data = philo->data;
	philo->fork[0] = &data->forky[(philo->p_nbr % data->num_philos)];
	philo->fork[1] = &data->forky[(philo->p_nbr - 1)];
	while (1 && data->live_status == 1 && philo->m_eaten < data->m2eat)
	{
		if (philo->p_nbr % 2 == 1 && philo->m_eaten == 0)
			wait_f(data->t2eat);
		if (data->live_status == 1)
			try_eating(philo);
		if (data->live_status == 1)
			try_sleeping(philo);
		if (data->live_status == 1)
			try_thinking(philo);
	}
	return (NULL);
}

//	stejna funkce jako vyse, pouze ve variante pro jednoho filozofa (zemre brzy)
void	*lets_live_short(void *phhill)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *) phhill;
	data = philo->data;
	printf("%lu %i %s\n", get_the_time(set_the_time()), 1, FORK);
	wait_f(data->t2die);
	message(philo, DEAD);
	data->live_status = 0;
	return (NULL);
}

//	funkce ve ktere filozofove jedi
void	try_eating(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->data->live_status != 1)
		return ;
//	zamykame prvni vidlicku pomoci pointeru na ni
	pthread_mutex_lock(philo->fork[0]);
	if (philo->data->live_status != 1)
		return ;
//	vypis stavu
	message(philo, FORK);
//	zamykame druhou vidlicku pomoci pointeru na ni
	pthread_mutex_lock(philo->fork[1]);
	if (philo->data->live_status != 1)
		return ;
	message(philo, FORK);
//	nastavujeme aktualni cas, kdy filozof naposledy jedl
	philo->eaten_last = set_the_time();
	message(philo, EAT);
//	tento status slouzi k rozliseni, kdy filozof ji, tak aby v te dobe nemohl zemrit
	philo->status = 1;
//	funkce wait_f k pozastaveni casu po dobu, kdy filozof ji
	wait_f(philo->data->t2eat);
	philo->status = 0;
//	update poctu snedenych jidel
	philo->m_eaten++;
//	odemknuti obou vidlicek
	unlock_forks(philo);
	return ;
}

//	funkce, ktera ma na starost filozofuv spanek
void	try_sleeping(t_philo *philo)
{
	if (philo->data->live_status == 1)
	{
		message(philo, SLEEP);
		wait_f(philo->data->t2sleep);
	}
}

//	funkce, ktra se stara o filozofovo mysleni
void	try_thinking(t_philo *philo)
{
	if (philo->data->live_status == 1)
		message(philo, THINK);
}
