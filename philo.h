#ifndef PHILO_H
#define PHILO_H
#include <pthread.h>
typedef struct s_main_struct t_main_struct;

typedef struct s_philo
{
	int flag;
	int philo_id;
	int total_meal_number;
	long last_meal_time;
	pthread_t filo_thread;
	t_main_struct *main_ref;
} t_philo;


typedef struct s_main_struct
{
	int time_to_eat;
	int time_to_sleep;
	int number_of_philo;
    int time_to_die;
    int stop_control;
    short died_id;
	int number_of_times_to_eat;
	t_philo *all_philos;
	pthread_t the_angel_of_death;
	pthread_mutex_t stop_mutex;
	pthread_mutex_t *forks_mutex;
	pthread_mutex_t message_mutex;
	long start_time;
} t_main_struct;





#endif