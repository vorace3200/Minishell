/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 00:28:14 by vorace32          #+#    #+#             */
/*   Updated: 2024/10/30 02:26:08 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXEC_H
# define MINISHELL_EXEC_H

# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define SUCCESS 0
# define ERROR -1
# define MALLOC_ERROR -2
# define FORK_ERROR -3
# define EXEC_ERROR -4

# define RESET "\033[0m"
# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"
# define BOLD "\033[1m"

typedef struct s_command
{
	char				**args;
	char				*cmd_path;
	int					pipe_in;
	int					pipe_out;
	int					redir_in;
	int					redir_out;
	struct s_command	*next;
	struct s_command	*prev;
}						t_command;

typedef struct s_shell
{
	char				**env;
	char				*input;
	t_command			*cmd_list;
	int					exit_status;
	int					is_running;
}						t_shell;

void					init_shell(t_shell *shell, char **env);
void					main_loop(t_shell *shell);
void					draw_logo(void);
void					delay_write(const char *prompt);

#endif