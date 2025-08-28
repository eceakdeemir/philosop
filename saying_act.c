/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   saying_act.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakdemi <ecakdemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 23:22:56 by ecakdemi          #+#    #+#             */
/*   Updated: 2025/08/29 00:33:46 by ecakdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void saying_act(t_philo *philo, char *message, int flag)
{
	int control_flag;

	pthread_mutex_lock(&(philo->main_ref->stop_mutex));
	control_flag = philo->main_ref->stop_control;
	pthread_mutex_unlock(&(philo->main_ref->stop_mutex));
	if (flag == 0)
	{
		pthread_mutex_lock(&(philo->main_ref->message_mutex));
		if (control_flag == 0)
			printf("%d. philo is %s timestamp: %ld\n", philo->philo_id + 1, message, ((get_current_millis() - philo->main_ref->start_time)));
		pthread_mutex_unlock(&(philo->main_ref->message_mutex));

	}
	else if (flag == 1)
	{
		pthread_mutex_lock(&(philo->main_ref->message_mutex));
		if (control_flag == 0)
			printf("%d. philo taken the %s fork timestamp: %ld\n", philo->philo_id + 1, message, ((get_current_millis() - philo->main_ref->start_time)));
		pthread_mutex_unlock(&(philo->main_ref->message_mutex));
	}
	else if (flag == 2)
	{
		pthread_mutex_lock(&(philo->main_ref->message_mutex));
		if (control_flag == 0)
			printf("%d. philo last meal time: %ld\n", philo->philo_id + 1, ((philo->last_meal_time - philo->main_ref->start_time)));
		pthread_mutex_unlock(&(philo->main_ref->message_mutex));
	}
}

