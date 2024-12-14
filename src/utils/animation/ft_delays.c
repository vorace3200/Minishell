/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 02:15:16 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/14 14:23:00 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

void	ft_delay(int milliseconds)
{
	volatile long long	count;
	long long			limit;

	count = 0;
	limit = milliseconds * 30000;
	while (count < limit)
		count++;
}

void	delay_write(const char *prompt)
{
	while (*prompt)
	{
		write(1, prompt, 1);
		ft_delay(1000);
		prompt++;
	}
}
