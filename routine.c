/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakdemi <ecakdemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 23:14:27 by ecakdemi          #+#    #+#             */
/*   Updated: 2025/08/29 02:21:46 by ecakdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void take_forks(t_philo *philo)
{
	if(philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		saying_act(philo, "has taken a fork", 1);
		pthread_mutex_lock(philo->right_fork);
		saying_act(philo, "has taken a fork", 1);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		saying_act(philo, "has taken a fork", 1);
		pthread_mutex_lock(philo->right_fork);
		saying_act(philo, "has taken a fork", 1);
	}
}

void *routine(void *philosophers)
{
	t_philo *philo;
	int stop;

	philo = (t_philo *)philosophers;
	if (philo->philo_id % 2 == 1)
		usleep(500); //0.5 ms -> bu deadlock ihtimali için yetmeyebilir 42de düzelt
	if (philo->left_fork == philo->right_fork)
	{
		pthread_mutex_lock(philo->left_fork);
		saying_act(philo, "has taken a fork", 0);
		ft_msleep(philo->main_ref->time_to_die);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	while (1)
	{
		//ölüm kontrol
		pthread_mutex_lock(&philo->main_ref->stop_mutex);
		stop = philo->main_ref->stop_control;
		pthread_mutex_unlock(&philo->main_ref->stop_mutex);
		if (stop != 0)
			break;
		take_forks(philo);
		//last meal time güncellemesi
		pthread_mutex_lock(&philo->main_ref->stop_mutex);
		philo->last_meal_time = (long)get_current_millis();
		pthread_mutex_unlock(&philo->main_ref->stop_mutex);
		//yemek
		saying_act(philo, "is eating", 0);
		ft_msleep(philo->main_ref->time_to_eat);
		//kaç kere yemek yedi
		philo->total_meal_number++;
		//take forksta aldığın çatalları sal, aldığın sırayla
		pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
		//filo yeme sınırına ulaştıysa döngüden çıksın
		if (philo->main_ref->number_of_times_to_eat > 0 &&
		philo->total_meal_number >= philo->main_ref->number_of_times_to_eat)
            break;
		saying_act(philo, "sleeping", 0);
		ft_msleep(philo->main_ref->time_to_sleep);
		saying_act(philo, "thinking", 0);
	}
	return (0);
}

