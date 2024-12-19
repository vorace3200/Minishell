/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrunier <tbrunier@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 01:38:03 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/19 15:14:17 by tbrunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

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
		add_history(shell->input);
		main_entry(shell);
		free(shell->input);
	}
	free_env(shell);
}
