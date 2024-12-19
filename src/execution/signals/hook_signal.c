/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 13:05:59 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/19 16:36:14 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

void	hook_signal(int signal)
{
	if (signal == SIGINT)
	{
		g_global_signal = 130;
		rl_replace_line("", 0);
		write(STDOUT_FILENO, "\n", 1);
		rl_forced_update_display();
	}
}

void	heredoc_signal(int signal)
{
	if (signal == SIGINT)
	{
		g_global_signal = 130;
	}
	else if (signal == SIGQUIT)
	{
		write(STDOUT_FILENO, "Quit (core dumped)\n", 18);
		exit(131);
	}
}

void	reset_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
