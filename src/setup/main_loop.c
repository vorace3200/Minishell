/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 01:38:03 by vorace32          #+#    #+#             */
/*   Updated: 2024/10/30 02:25:44 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell_exec.h"

void	main_loop(t_shell *shell)
{
	draw_logo();
	while (shell->is_running)
	{
		delay_write("\033[0;32mminishell$ \033[0m");
		shell->input = readline("");
		if (shell->input == NULL)
		{
			shell->is_running = 0;
			break ;
		}
		add_history(shell->input);
		printf("input: %s\n", shell->input);
		free(shell->input);
	}
}
