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

#include "../include/philo.h"




int main(int argc, char* argv[])
{
	t_data *data;
	t_philo	*philo;
	int	i;
	
	i = 0;
	if (input_controll(argc, argv))
		return(1);
	data = fill_data(argc, argv);
//	fprintf(stderr, "data->num_philos: %d\n", data->num_philos);
	while(i < data->num_philos)
	{
		philo = init_philos(i, data);
		pthread_create(&(data->thread[i]), NULL, lets_live, (void*) philo);
		i++;
//		usleep(100);
	}
	threads_join(data);
	cleaning(data);
	return (0);
}



t_data	*fill_data(int argc, char **argv)
{
	t_data *data;
	t_philo	*philo;
	int	i = 0;
	
	data = malloc(sizeof(t_data));
	if (!data)
		return(NULL);
	data->num_philos = ft_atoi(argv[1]);
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	data->thread = malloc(sizeof(pthread_t) * data->num_philos);
	data->forks = malloc(sizeof(t_forks) * data->num_philos);
	if(!data->philos || !data->thread || !data->forks)
		return (NULL);
	while(i < data->num_philos)
	{
		data->forks[i].f_number = i + 1;
		data->forks[i].f_status = 0;
		i++;
	}
	data->t2die = ft_atoi(argv[2]);
	data->t2eat = ft_atoi(argv[3]);
	data->t2sleep = ft_atoi(argv[4]);
	if (argc == 6 && ft_atoi(argv[5]) >=0)
		data->m2eat = ft_atoi(argv[5]);
	else
		data->m2eat = 0;
	data->live_status = 1;
	pthread_mutex_init(&data->report, NULL);
	data->start_time = set_the_time();
	data->curr_time = get_the_time(data->start_time);
	return(data);

}
t_philo	*init_philos(int i, t_data *data)
{
	t_philo *philo;
	
	philo = &data->philos[i];
	philo->data = data;
	philo->p_nbr = i + 1;
	philo->m_eaten = 0;
	philo->eaten_last = set_the_time();
	fprintf(stderr, "philo->p_nbr: %d\n", philo->p_nbr);
	return(philo);
}
void	threads_join(t_data *data)
{
	t_philo *philo;
	int	i;
	
	philo = data->philos;
	i = 0;
	while (i < data->num_philos)
	{
		//usleep(100000);
		fprintf(stderr, "%lu Im dying an my nbr is %d\n",get_the_time(data->start_time), philo[i].p_nbr);
		pthread_join(data->thread[i], NULL);	
		i++;
	}
}
void	*lets_live(void *phhill)
{
	t_philo	*philo;
	t_data	*data;
	
	philo = (t_philo *) phhill;
	data = philo->data;
	int	i = 0;
/*	while (1 && life_guard == 0)
	{
		
	*/
	
	
	try_eating(philo, data);
	
	
	
	
	
/*	usleep(10000);
	while(i <= 10000)
	{
		if(i % 1000 == 0)
			fprintf(stderr, "%lu Im alive my number is %d and i is: %d\n", get_the_time(data->start_time),  philo->p_nbr, i);
		i++;
	}*/
//	pthread_mutex_unlock(&data->report);
	return(NULL);
}

void	try_eating(t_philo *philo, t_data *data)
{
	int	i = 0;
	t_forks *forks = data->forks;
	
//	if(
	
	
	
//	pthread_mutex_lock(&
	wait_f(200);
	philo->eaten_last = get_the_time(philo->eaten_last);
	fprintf(stderr, "%i eaten_last: %lu\n", philo->p_nbr, philo->eaten_last);
	life_guard(philo);
	while(i < data->num_philos)
	{
		fprintf(stderr, "%lu cislo vidlicky: %d\n", get_the_time(data->start_time), forks[i].f_number);
		i++;
	}
//	pthread_mutex_unlock(&
}
void	cleaning(t_data *data)
{
	int	i = -1;
	
//	while(++i < data->num_philos)
		free(data->philos);
	pthread_mutex_destroy(&data->report);
	free(data);
}
