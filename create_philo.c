/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakdemi <ecakdemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 19:33:47 by ecakdemi          #+#    #+#             */
/*   Updated: 2025/08/29 23:10:09 by ecakdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_philo_array(t_main_struct *main_struct)
{
	int	i;

	i = 0;
	while (i < main_struct->number_of_philo)
	{
		main_struct->all_philos[i].philo_id = i;
		main_struct->all_philos[i].main_ref = main_struct;
		main_struct->all_philos[i].left_fork = &main_struct->forks_mutex[i];
		main_struct->all_philos[i].right_fork = &main_struct->forks_mutex[(i
				+ 1) % main_struct->number_of_philo];
		main_struct->all_philos[i].total_meal_number = 0;
		main_struct->all_philos[i].flag = 0;
		main_struct->all_philos[i].last_meal_time = 0;
		i++;
	}
}

void	create_philo_thread(t_main_struct *main_struct)
{
	int	i;

	i = 0;
	while (i < main_struct->number_of_philo)
	{
		pthread_create(&(main_struct->all_philos[i].filo_thread), NULL, routine,
			&(main_struct->all_philos[i]));
		i++;
	}
}
