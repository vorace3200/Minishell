/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_entry.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:53:50 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/12 23:00:48 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell_exec.h"

void	main_entry(t_shell *shell)
{
	t_command	*cmd;

	main_parsing(shell);
	cmd = shell->cmd_list;
	while (cmd)
	{
		if (cmd->args && ft_strcmp(cmd->args[0], "exit") == 0)
		{
			builtin_exit(shell, cmd->args);
			return ;
		}
		cmd = cmd->next;
	}
	execute_commands(shell);
	free_commands(shell->cmd_list);
	shell->cmd_list = NULL;
}
