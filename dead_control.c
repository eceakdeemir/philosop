/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakdemi <ecakdemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 00:37:36 by ecakdemi          #+#    #+#             */
/*   Updated: 2025/08/29 02:26:12 by ecakdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int one_philo_dead_control_for_monitor(t_philo *philo)
{
	unsigned long last;
	unsigned long now;
	int stop;

	now = get_current_millis();
	pthread_mutex_lock(&philo->main_ref->stop_mutex);
	last = (unsigned long)philo->last_meal_time;
	stop = philo->main_ref->stop_control;
	pthread_mutex_unlock(&philo->main_ref->stop_mutex);
	//ya biri öldü ya herkes doydu, devam etmeye gerek yok.
	if (stop != 0)
		return (0);
	if (now - last >= (unsigned long)philo->main_ref->time_to_die)
	{
		pthread_mutex_lock(&philo->main_ref->stop_mutex);
		if (philo->main_ref->stop_control == 0)
		{
			philo->main_ref->stop_control = -1;
			philo->main_ref->died_id = philo->philo_id;
		}
		saying_act(philo, "died", 0);
		pthread_mutex_unlock(&philo->main_ref->stop_mutex);
		return (-1);
	}
	return (0);
}

void *monitor_thread_dead_control(void *main_struct)
{
	t_main_struct *main_s;
	int i;
	int everyone_eat;

	main_s = main_struct;
	while (1)
	{
		if (main_s->number_of_times_to_eat > 0)
			everyone_eat = 1;
		else
			everyone_eat = 0;
		i = 0;
		while (i < main_s->number_of_philo)
		{
			if (one_philo_dead_control_for_monitor(&main_s->all_philos[i]) == -1)
				return (NULL);
			if (main_s->number_of_times_to_eat > 0 && main_s->all_philos[i].total_meal_number < main_s->number_of_times_to_eat)
				everyone_eat = 0;
			i++;
		}
	}
	if (main_s->number_of_times_to_eat > 0 && everyone_eat)
	{
		pthread_mutex_lock(&main_s->stop_mutex);
		if (main_s->stop_control == 0)
			main_s->stop_control = 1;
		pthread_mutex_unlock(&main_s->stop_mutex);
		return (NULL);
	}
	usleep(500);
	return (NULL);
}


