/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiharel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 14:51:15 by wiharel           #+#    #+#             */
/*   Updated: 2022/08/23 14:51:17 by wiharel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	r_take_fork(t_philo *philo)
{
	if (philo->num % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->m_forks[philo->i_fork1]);
		pthread_mutex_lock(&philo->data->m_forks[philo->i_fork2]);
	}
	else
	{
		pthread_mutex_lock(&philo->data->m_forks[philo->i_fork2]);
		pthread_mutex_lock(&philo->data->m_forks[philo->i_fork1]);
	}
	display(philo, MSG_FORKS);
	display(philo, MSG_FORKS);
}

void	r_eat(t_philo *philo)
{
	display(philo, MSG_EAT);
	sleep_ajusted(philo->time->ms_to_eat);
	pthread_mutex_unlock(&philo->data->m_forks[philo->i_fork1]);
	pthread_mutex_unlock(&philo->data->m_forks[philo->i_fork2]);
}

void	r_sleep(t_philo *philo)
{
	display(philo, MSG_SLEEP);
	sleep_ajusted(philo->time->ms_to_sleep);
}

void	display(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->data->m_life);
	philo->ms_current = get_time() - philo->time->ms_start;
	if (!(philo->data->first_dead || philo->data->all_ate))
	{
		printf("%lld	%d	%s.\n", philo->ms_current, philo->num, action);
		if (ft_strcmp(action, MSG_EAT) == 0)
		{
			philo->ms_to_die = philo->ms_current + philo->time->ms_to_die;
			philo->eat_count += 1;
		}
	}
	pthread_mutex_unlock(&philo->data->m_life);
}

void	r_think(t_philo *philo)
{
	display(philo, MSG_THINK);
}
