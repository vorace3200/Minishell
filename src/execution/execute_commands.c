/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:29:05 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/12 10:33:00 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell_exec.h"

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

void	execute_commands(t_shell *shell)
{
	t_command	*cmd;
	pid_t		pid;
	int			status;

	cmd = shell->cmd_list;
	while (cmd)
	{
		setup_pipes(cmd);
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (!pid)
			execute_command(cmd, shell);
		if (cmd->pipe_in_fd != -1)
			close(cmd->pipe_in_fd);
		if (cmd->pipe_out_fd != -1)
			close(cmd->pipe_out_fd);
		cmd = cmd->next;
	}
	while (wait(&status) > 0)
		;
	shell->exit_status = WEXITSTATUS(status);
}
