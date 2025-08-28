/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_error_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakdemi <ecakdemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 19:04:36 by ecakdemi          #+#    #+#             */
/*   Updated: 2025/08/28 17:20:45 by ecakdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_is_all_digit(char *arg_str)
{
	int i;

	i = 0;
	while(arg_str[i])
	{
		if (!(arg_str[i] >= '0' && arg_str[i] <= '9'))
			return (-1);
		i++;	
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	i;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - 48;
		i++;
	}
	return (result * sign);
}

int arg_parse(char *arg_str)
{
	if (ft_is_all_digit(arg_str) == -1)
	{
		printf("ARG NUMBER ERROR\n");
		return (-1);
	}
	return (0);
}

int arg_number(int ac, char **av)
{
    if (ac != 5 && ac != 6)
    {
        printf("arg count error\n");
        return (-1);
    }
	if (ac == 6)
	{
		if (ft_atoi(av[5]) < 0 || arg_parse(av[5]) == -1)
		{
			printf("PHILO MUST EAT ERROR\n");
			return (-1);
		}
	}
	return (0);
}

int arg_check_error(int ac, char **av)
{
	if (arg_number(ac, av) != 0)
		return (-1);
	if (ft_atoi(av[1]) > 200 || arg_parse(av[1]) == -1 || ft_atoi(av[1]) == 0)
	{
		printf("PHILO NUMBER ERROR\n");
		return (-1);
	}
	if (ft_atoi(av[2]) <= 0 || arg_parse(av[2]) == -1)
	{
		printf("PHILO DIE TIME ERROR\n");
		return (-1);
	}
	if (ft_atoi(av[3]) <= 0 || arg_parse(av[3]) == -1)
	{
		printf("PHILO EAT TIME ERROR\n");
		return (-1);
	}
	if (ft_atoi(av[4]) <= 0 || arg_parse(av[4]) == -1)
	{
		printf("PHILO SLEEP TIME ERROR\n");
		return (-1);
	}
	return (0);
}
