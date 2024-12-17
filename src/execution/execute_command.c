/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 23:05:49 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/17 17:07:06 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	skip_invalid_command(t_command *cmd, t_shell *shell)
{
	if (cmd->invalid == 1)
	{
		shell->exit_status = 1;
		return (1);
	}
	return (0);
}

void	fork_and_execute(t_command *cmd, t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		execute_child_process(cmd, shell);
}

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
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(" command not found\n", 2);
		exit(127);
	}
}
