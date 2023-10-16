/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiharel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 14:50:29 by wiharel           #+#    #+#             */
/*   Updated: 2022/08/23 14:50:32 by wiharel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_time {
	long long	ms_start;
	long long	ms_to_die;
	long long	ms_to_eat;
	long long	ms_to_sleep;
	int			count_to_eat;
}	t_time;

typedef struct s_philo {
	int				num;
	int				eat_count;
	int				i_fork1;
	int				i_fork2;
	long long		ms_to_die;
	long long		ms_current;
	pthread_t		thread;
	t_time			*time;
	struct s_data	*data;
}	t_philo;

typedef struct s_data {
	int				nb_philos;
	int				first_dead;
	int				all_ate;
	long long		ms_current;
	t_philo			*philos;
	pthread_mutex_t	*m_forks;
	pthread_mutex_t	m_life;
}	t_data;

# define INT_MAX 2147483647
# define INT_MIN -2147483648

# define M_SUCCESS 0

# define MSG_FORKS "has taken a fork"
# define MSG_EAT "is eating"
# define MSG_SLEEP "is sleeping"
# define MSG_THINK "is thinking"

# define COLOR_RED "\033[0;32m"
# define COLOR_PURPLE "\033[0;36m"
# define COLOR_DEFAULT "\033[0m"

void		r_take_fork(t_philo *philo);
void		r_eat(t_philo *philo);
void		r_sleep(t_philo *philo);
void		r_think(t_philo *philo);
void		display(t_philo *philo, char *action);
void		*routine(void *param);
int			init(t_data *data, t_time *time);
void		free_all(t_data *data);
void		destroy_all(t_data *data);
int			print_error_u(const char *msg);
int			ft_strlen(char *str);
int			ft_atoi(char *str);
int			ft_strcmp(const char *s1, const char *s2);
long long	get_time(void);
int			print_error_i(const char *msg);
void		sleep_ajusted(long long ms);
#endif
