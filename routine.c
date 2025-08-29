/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakdemi <ecakdemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 23:14:27 by ecakdemi          #+#    #+#             */
/*   Updated: 2025/08/29 23:12:05 by ecakdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death_status(t_philo *philo)
{
	int	stop;

	pthread_mutex_lock(&philo->main_ref->stop_mutex);
	stop = philo->main_ref->stop_control;
	pthread_mutex_unlock(&philo->main_ref->stop_mutex);
	return (stop != 0);
}

void	take_forks(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		saying_act(philo, "has taken a fork", 1);
		pthread_mutex_lock(philo->right_fork);
		saying_act(philo, "has taken a fork", 1);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		saying_act(philo, "has taken a fork", 1);
		pthread_mutex_lock(philo->left_fork);
		saying_act(philo, "has taken a fork", 1);
	}
}

int	check_death_status_and_return(t_philo *philo)
{
	if (philo->main_ref->eat_number > 0
		&& philo->total_meal_number >= philo->main_ref->eat_number)
		return (1);
	if (check_death_status(philo))
		return (1);
	saying_act(philo, "sleeping", 0);
	ft_msleep(philo->main_ref->time_to_sleep);
	if (check_death_status(philo))
		return (1);
	saying_act(philo, "thinking", 0);
	return (0);
}

int	one_philo_routine(t_philo *philo)
{
	if (philo->left_fork == philo->right_fork)
	{
		pthread_mutex_lock(philo->left_fork);
		saying_act(philo, "has taken a fork", 0);
		ft_msleep(philo->main_ref->time_to_die);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	return (0);
}

void	*routine(void *philosophers)
{
	t_philo	*philo;

	philo = (t_philo *)philosophers;
	if (philo->philo_id % 2 == 1)
		usleep(500);
	if (one_philo_routine(philo))
		return (NULL);
	while (1)
	{
		if (check_death_status(philo))
			break ;
		take_forks(philo);
		pthread_mutex_lock(&philo->main_ref->stop_mutex);
		philo->last_meal_time = (long)get_current_millis();
		pthread_mutex_unlock(&philo->main_ref->stop_mutex);
		saying_act(philo, "is eating", 0);
		ft_msleep(philo->main_ref->time_to_eat);
		philo->total_meal_number++;
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		if (check_death_status_and_return(philo))
			break ;
	}
	return (0);
}
