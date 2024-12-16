/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 23:05:49 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/16 12:51:43 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	redirect_fds(t_command *cmd)
{
	if (cmd->redir_in != -1)
	{
		if (dup2(cmd->redir_in, STDIN_FILENO) == -1)
		{
			ft_putstr_fd("Error: Failed to redirect input\n", 2);
			return (-1);
		}
		close(cmd->redir_in);
	}
	if (cmd->redir_out != -1)
	{
		if (dup2(cmd->redir_out, STDOUT_FILENO) == -1)
		{
			ft_putstr_fd("Error: Failed to redirect output\n", 2);
			return (-1);
		}
		close(cmd->redir_out);
	}
	return (0);
}

void	execute_command(t_command *cmd, t_shell *shell)
{
	redirect_fds(cmd);
	if (is_builtin(cmd->args))
	{
		execute_builtin(shell, cmd->args);
		exit(shell->exit_status);
	}
	if (execvp(cmd->args[0], cmd->args) == -1)
	{
		perror("execvp");
		exit(EXIT_FAILURE);
	}
}
