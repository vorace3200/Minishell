/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 01:38:03 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/19 16:15:26 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int		g_global_signal = 0;

void	main_loop(t_shell *shell)
{
	shell->is_running = 1;
	draw_logo();
	while (shell->is_running)
	{
		setup_signal();
		shell->input = readline(PROMPT);
		if (!shell->input)
		{
			shell->is_running = 0;
			break ;
		}
		if (!is_input_empty(shell->input))
			add_history(shell->input);
		main_entry(shell);
		free(shell->input);
		if (g_global_signal == 130)
		{
			g_global_signal = 0;
			continue ;
		}
	}
	free_env(shell);
}
