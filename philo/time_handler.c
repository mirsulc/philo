/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msulc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 09:44:33 by msulc             #+#    #+#             */
/*   Updated: 2023/09/27 09:44:38 by msulc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//	tato funkce slouzi k urceni presneho casu
unsigned long	set_the_time(void)
{
	struct timeval		time;
	int					moment;

	gettimeofday(&time, NULL);
	moment = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (moment);
}

//	tato fce slouzi k urceni intervalu od urciteho bodu v case (treba startu) do aktualniho casu
unsigned long	get_the_time(unsigned long start)
{
	struct timeval		time2;
	int					curr;

	gettimeofday(&time2, NULL);
	curr = ((time2.tv_sec * 1000) + (time2.tv_usec / 1000)) - start;
	return (curr);
}

//	funkce, ktera se stara o zadane casy t2eat, t2die, t2sleep
unsigned long	wait_f(unsigned long time)
{
	return (usleep(time * 1000));
}
