/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msulc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 10:16:39 by msulc             #+#    #+#             */
/*   Updated: 2023/09/19 10:16:41 by msulc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	int	while_function(const char *str, int result, int i)
{
	while (str[i] >= 48 && str[i] <= 57)
	{
		result = result * 10;
		result = result + (str[i] - 48);
		i++;
	}
	return (result);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	minus;

	i = 0;
	result = 0;
	minus = 1;
	while (str[i])
	{
		if (str[i] < 9 || (str[i] > 13 && str[i] < 32)
			|| (str[i] > 32 && str[i] < 43) || str[i] == 44
			|| (str[i] > 45 && str[i] < 48) || str[i] > 57
			|| ((str[i] == '-' || str[i] == '+') && (str[i + 1] < 48
					|| str[i + 1] > 57)))
			return (0);
		if (str[i] == '-')
			minus = minus * -1;
		if (str[i] >= 48 && str[i] <= 57)
		{
			result = while_function(str, result, i) * minus;
			return (result);
		}
		i++;
	}
	return (result);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

//	kontrola vstupnich argumentu 
int	ft_looking_for_characters(char **argv)
{
	int	i;
	int	y;

	i = 1;
	while (argv[i])
	{
		y = 0;
		while (argv[i][y])
		{
			if (ft_isdigit(argv[i][y]) == 0)
				return (1);
			y++;
		}
		i++;
	}
	return (0);
}
