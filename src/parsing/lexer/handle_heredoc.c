/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:35:49 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/16 23:39:00 by vorace32         ###   ########.fr       */
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

void	write_heredoc_lines(int write_end, char *delim)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, write_end);
		ft_putstr_fd("\n", write_end);
		free(line);
	}
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
	close_heredoc_fds(write_end);
	if (cmd->redir_in != -1)
		close(cmd->redir_in);
	cmd->redir_in = read_end;
}
