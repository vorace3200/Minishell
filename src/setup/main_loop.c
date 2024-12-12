/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 01:38:03 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/12 10:27:43 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell_exec.h"

void	main_loop(t_shell *shell)
{
	shell->is_running = 1;
	draw_logo();
	while (shell->is_running)
	{
		shell->input = readline("\033[0;32mminishell$\033[0m ");
		if (shell->input == NULL)
		{
			shell->is_running = 0;
			break ;
		}
		add_history(shell->input);
		main_entry(shell);
		free(shell->input);
	}
}
