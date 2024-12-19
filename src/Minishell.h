/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 00:28:14 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/19 01:02:02 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/fcntl.h>
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

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_D_REDIR_IN,
	TOKEN_D_REDIR_OUT,
	TOKEN_EOF
}						t_token_type;

typedef struct s_token
{
	char				*value;
	t_token_type		type;
	struct s_token		*next;
	struct s_token		*prev;
	int					was_single_quoted;
	int					was_double_quoted;
}						t_token;

typedef struct s_command
{
	char				**args;
	int					args_size;
	int					args_count;
	char				*cmd_path;
	int					pipe_in;
	int					pipe_out;
	int					pipe_in_fd;
	int					pipe_out_fd;
	int					redir_in;
	int					redir_out;
	int					invalid;
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
	int					have_pipe;
}						t_shell;

typedef struct s_quote_process
{
	t_shell				*shell;
	const char			*arg;
	int					*i;
	char				**res;
	int					in_single;
}						t_quote_process;

// ==================== [ Signals ] ==================== //
void					hook_signal(int signal);
void					setup_signal(void);

// ==================== [ Execution ] ==================== //
void					execute_commands(t_shell *shell);
void					execute_command(t_command *cmd, t_shell *shell);
int						skip_invalid_command(t_command *cmd, t_shell *shell);
void					fork_and_execute(t_command *cmd, t_shell *shell);
void					execute_child_process(t_command *cmd, t_shell *shell);

// ==================== [ Builtins ] ==================== //
int						is_builtin(char **args);
int						execute_builtin(t_shell *shell, char **args);
void					builtin_echo(t_shell *shell, char **args);
void					builtin_exit(t_shell *shell, char **args);
void					builtin_pwd(t_shell *shell);
void					builtin_cd(t_shell *shell, char **args);
void					builtin_env(t_shell *shell);
void					builtin_export(t_shell *shell, char **args);
void					builtin_unset(t_shell *shell, char **args);

// ==================== [ Environement ] ==================== //
char					*get_env_value(t_shell *shell, char *env_name);
int						set_env_value(t_shell *shell, const char *env_name,
							const char *value);
int						unset_env_value(t_shell *shell, const char *env_name);
int						env_count(char **env);
void					expand_variables(t_shell *shell);
char					*find_command_in_path(const char *cmd,
							const char *path);
char					*get_var_name(const char *str, int *len);
// ==================== [ Command ] ==================== //
void					add_redirection_to_command(t_command *cmd,
							t_token_type type, char *filename);
void					add_argument_to_command(t_command *cmd, char *arg);

// ==================== [ Free ] ==================== //
void					free_tokens(t_token *tokens);
void					free_commands(t_command *cmd_list);
void					free_env(t_shell *shell);
// ==================== [ Lexer ] ==================== //
t_token					*lexer(const char *input);
void					handle_word(const char *input, int *i, t_token **tokens,
							t_token **tail);
int						handle_quotes(char **input, int *i, t_token **tokens,
							t_token **tail);
int						handle_redirection(const char *input, int *i,
							t_token **tokens, t_token **tail);
int						handle_pipe(const char *input, int *i, t_token **tokens,
							t_token **tail);
void					handle_heredoc(t_command *cmd, char *delimiter);
// ==================== [ Token ] ==================== //
t_token					*create_token(char *value, t_token_type type);
void					add_token(t_token **head, t_token **tail,
							t_token *new_token);
// ==================== [ Parsing ] ==================== //
void					main_parsing(t_shell *shell);
void					handle_command_list(t_token *tokens, t_shell *shell);

// ==================== [ Node ] ==================== //
t_command				*new_command_node(void);

// ==================== [ Utils ] ==================== //
void					delay_write(const char *prompt);
void					draw_logo(void);
char					**ft_split(char const *s, char c);
void					ft_free_split(char **split);
char					*ft_strncpy(char *dest, const char *src, size_t n);
char					*ft_strdup(const char *s);
char					*ft_strndup(const char *s, size_t n);
int						ft_isspace(int c);
void					ft_putstr_fd(char *s, int fd);
int						ft_strlen(const char *c);
char					*ft_strjoin_free(char *s1, char *s2);
char					*ft_strjoin(char const *s1, char const *s2);
void					*ft_memcpy(void *dest, const void *src, size_t n);
int						ft_strcmp(const char *s1, const char *s2);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*process_char(t_shell *shell, const char *arg, int *i,
							char **res);
char					*ft_strchr(const char *s, int c);
int						ft_isalnum(int c);
int						ft_isdigit(int c);
void					handle_execve_error(char *cmd);
void					restore_fds(int saved_stdin, int saved_stdout);
void					close_fds(t_command *cmd);
int						save_std_fds(int *saved_stdin, int *saved_stdout);
int						redirect_fds(t_command *cmd);
char					*ft_itoa(int n);
// ==================== [ Handle ] ==================== //
void					handle_command(t_shell *shell);
void					handle_input_redir(t_command *cmd, char *file);
void					handle_output_redir(t_command *cmd, char *file,
							int append);
// ==================== [ Setup ] ==================== //
void					init_shell(t_shell *shell, char **env);
void					main_loop(t_shell *shell);
void					main_entry(t_shell *shell);

#endif