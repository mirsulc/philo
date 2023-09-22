/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msulc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:28:55 by msulc             #+#    #+#             */
/*   Updated: 2023/09/18 16:30:05 by msulc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

# define FORK	"has taken fork"
# define EAT	"is eating"
# define SLEEP	"is sleeping"
# define THINK	"is thinking"
# define DEAD	"has just died"


struct	s_philo;

typedef struct	s_forks
{
	int	f_number;
	int	f_status;
}	t_forks;

typedef struct s_data
{
	int		num_philos;
	struct s_philo	*philos;
	int		t2die;
	int		t2eat;
	int		t2sleep;
	int		t2think;
	int		m2eat;
	int		live_status;
	unsigned long	start_time;
	unsigned long	curr_time;
	pthread_t	*thread;
	pthread_t	guard;
	t_forks		*forks;
	//pthread_t	controller;
	pthread_mutex_t	report;
	pthread_mutex_t	*forky;
}	t_data;

typedef struct s_philo
{
	t_data		*data;
	int		p_nbr;
	int		m_eaten;
	unsigned long	eaten_last;
	
	pthread_mutex_t	fork[2];
	
	
}	t_philo;


int	input_controll(int argc, char **argv);
int	ft_atoi(const char *str);
int	ft_isdigit(int c);
int	ft_looking_for_characters(char **argv);
t_data	*fill_data(int argc, char **argv);
unsigned long	set_the_time(void);
t_philo	*init_philos(int i, t_data *data);
unsigned long	get_the_time(unsigned long start);
void	threads_join(t_data *data);
void	*lets_live();
void	try_eating(t_philo *philo, t_data *data);

void	cleaning(t_data *data);
unsigned long	wait_f(unsigned long time);
int	life_guard(t_philo *philo);
void	message(t_philo *philo, char *state);

#endif
