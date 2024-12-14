/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 23:02:58 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/14 14:21:56 by vorace32         ###   ########.fr       */
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

static void	handle_child_process(t_command *cmd, t_shell *shell)
{
	if (cmd->pipe_in_fd != -1)
		close(cmd->pipe_in_fd);
	if (cmd->pipe_out_fd != -1)
		close(cmd->pipe_out_fd);
	execute_command(cmd, shell);
}

static void	close_fds(t_command *cmd)
{
	if (cmd->pipe_in_fd != -1)
		close(cmd->pipe_in_fd);
	if (cmd->pipe_out_fd != -1)
		close(cmd->pipe_out_fd);
}

void	execute_commands(t_shell *shell)
{
	t_command	*cmd;
	pid_t		pid;
	int			status;

	cmd = shell->cmd_list;
	if (cmd && cmd->next == NULL && is_builtin(cmd->args))
	{
		redirect_fds(cmd);
		execute_builtin(shell, cmd->args);
		return ;
	}
	while (cmd)
	{
		setup_pipes(cmd);
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		if (pid == 0)
			handle_child_process(cmd, shell);
		close_fds(cmd);
		cmd = cmd->next;
	}
	while (wait(&status) > 0)
		;
	shell->exit_status = WEXITSTATUS(status);
}
