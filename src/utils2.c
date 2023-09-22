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

#include "../include/philo.h"

int	input_controll(int argc, char **argv)
{

	if (argc != 5 && argc != 6)
		return (printf("Wrong number of arguments\n"), 1);
	if (ft_looking_for_characters(argv))
		return (printf("Only numeric arguments and positive numbers are accepted\n"), 1);
	if (ft_atoi(argv[1]) < 0 || ft_atoi(argv[2]) < 0
		|| ft_atoi(argv[3]) < 0 || ft_atoi(argv[4]) < 0)
		return (printf("All arguments need to be positive numbers\n"), 1);
	if (ft_atoi(argv[1]) == 1)
		return (printf("Having only one fork, he died on starvation\n"), 1);
	return (0);
}

unsigned long	wait_f(unsigned long time)
{
	return (usleep(time * 1000));
}

int	life_guard(t_philo *philo)
{
//	fprintf(stderr, "eaten_last: %lu to_die: %i\n", philo->eaten_last, philo->data->t2die);
	if(philo->eaten_last >= philo->data->t2die)
	{
		//fprintf(stderr, "eaten_last: %lu to_die: %i\n", philo->eaten_last, philo->data->t2die);
		message(philo, DEAD);
		philo->data->live_status = 0;
		return (1);
	}
	return (0);
}

void	message(t_philo *philo, char *state)
{
//	fprintf(stderr, "state: %s\n", state);	
	pthread_mutex_lock(&philo->data->report);
//	fprintf(stderr, "philo->p_nbr: %i\n", philo->p_nbr);
	printf("%lu %i %s\n", get_the_time(philo->data->start_time), philo->p_nbr, state);
	pthread_mutex_unlock(&philo->data->report);
	return ;
}
