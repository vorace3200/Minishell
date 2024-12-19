/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:35:49 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/19 17:28:50 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int	create_heredoc_pipe(void)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
	{
		ft_putstr_fd("[ERROR] pipe creation failed\n", 2);
		return (-1);
	}
	return (pipefd[0] << 16 | pipefd[1]);
}

void	close_heredoc_fds(int write_end)
{
	close(write_end);
}

static int	process_heredoc_line(char *line, char *delimiter, int write_end)
{
	if (g_global_signal == 130)
	{
		if (line)
			free(line);
		close(write_end);
		return (1);
	}
	if (!line || ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (1);
	}
	ft_putstr_fd(line, write_end);
	ft_putstr_fd("\n", write_end);
	free(line);
	return (0);
}

void	write_heredoc_lines(int write_end, char *delim)
{
	char	*line;
	int		should_break;

	g_global_signal = 0;
	should_break = 0;
	signal(SIGINT, heredoc_signal);
	while (!should_break)
	{
		line = readline("> ");
		should_break = process_heredoc_line(line, delim, write_end);
	}
	reset_signal();
}

void	handle_heredoc(t_command *cmd, char *delimiter)
{
	int	combined;
	int	read_end;
	int	write_end;

	combined = create_heredoc_pipe();
	if (combined == -1)
		return ;
	read_end = combined >> 16;
	write_end = combined & 0xFFFF;
	write_heredoc_lines(write_end, delimiter);
	if (g_global_signal == 130)
	{
		close(read_end);
		cmd->invalid = 1;
		return ;
	}
	close(write_end);
	if (cmd->redir_in != -1)
		close(cmd->redir_in);
	cmd->redir_in = read_end;
}
