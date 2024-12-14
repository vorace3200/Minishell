/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 23:05:49 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/14 14:21:55 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

void	redirect_fds(t_command *cmd)
{
	if (cmd->redir_in != -1)
	{
		dup2(cmd->redir_in, STDIN_FILENO);
		close(cmd->redir_in);
	}
	else if (cmd->pipe_in_fd != -1)
	{
		dup2(cmd->pipe_in_fd, STDIN_FILENO);
		close(cmd->pipe_in_fd);
	}
	if (cmd->redir_out != -1)
	{
		dup2(cmd->redir_out, STDOUT_FILENO);
		close(cmd->redir_out);
	}
	else if (cmd->pipe_out_fd != -1)
	{
		dup2(cmd->pipe_out_fd, STDOUT_FILENO);
		close(cmd->pipe_out_fd);
	}
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
