/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 23:02:58 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/18 22:19:14 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

static void	setup_pipes(t_command *cmd)
{
	int	pipefd[2];

	if (cmd->pipe_out)
	{
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		cmd->pipe_out_fd = pipefd[1];
		if (cmd->next)
			cmd->next->pipe_in_fd = pipefd[0];
		else
			close(pipefd[0]);
	}
	else
		cmd->pipe_out_fd = -1;
}

static void	execute_single_builtin(t_shell *shell, t_command *cmd)
{
	int	saved_stdin;
	int	saved_stdout;

	if (save_std_fds(&saved_stdin, &saved_stdout) == -1)
		return ;
	if (redirect_fds(cmd) == -1)
	{
		restore_fds(saved_stdin, saved_stdout);
		return ;
	}
	execute_builtin(shell, cmd->args);
	restore_fds(saved_stdin, saved_stdout);
}

void	execute_child_process(t_command *cmd, t_shell *shell)
{
	if (cmd->pipe_in_fd != -1)
		dup2(cmd->pipe_in_fd, STDIN_FILENO);
	if (cmd->pipe_out_fd != -1)
		dup2(cmd->pipe_out_fd, STDOUT_FILENO);
	close_fds(cmd);
	execute_command(cmd, shell);
}

static void	execute_multiple_commands(t_shell *shell)
{
	t_command	*cmd;
	int			status;

	cmd = shell->cmd_list;
	while (cmd)
	{
		if (cmd->invalid == 1)
		{
			shell->exit_status = 1;
			return ;
		}
		setup_pipes(cmd);
		if (skip_invalid_command(cmd, shell))
		{
			cmd = cmd->next;
			continue ;
		}
		fork_and_execute(cmd, shell);
		close_fds(cmd);
		cmd = cmd->next;
	}
	while (wait(&status) > 0)
		;
	shell->exit_status = WEXITSTATUS(status);
}

void	execute_commands(t_shell *shell)
{
	if (shell->cmd_list && shell->cmd_list->next == NULL
		&& is_builtin(shell->cmd_list->args))
	{
		shell->have_pipe = 0;
		execute_single_builtin(shell, shell->cmd_list);
	}
	else
	{
		shell->have_pipe = 1;
		execute_multiple_commands(shell);
	}
}
