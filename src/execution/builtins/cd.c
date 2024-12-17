/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:42:39 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/17 17:15:25 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

char	*get_cd_target(t_shell *shell, char **args)
{
	char	*dir;

	if (args[1] == NULL)
		dir = get_env_value(shell, "HOME");
	else if (ft_strcmp(args[1], "-") == 0)
	{
		dir = get_env_value(shell, "OLDPWD");
		if (!dir)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			return (NULL);
		}
	}
	else
		dir = args[1];
	return (dir);
}

int	change_directory(char *dir)
{
	if (chdir(dir) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(dir, 2);
		ft_putstr_fd(": not a directory\n", 2);
		return (1);
	}
	return (0);
}

int	is_cd_dash(char **args)
{
	if (args[1] && ft_strcmp(args[1], "-") == 0)
		return (1);
	return (0);
}

void	update_cd_env(t_shell *shell, char *old_pwd)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
	{
		set_env_value(shell, "OLDPWD", old_pwd);
		set_env_value(shell, "PWD", cwd);
	}
}

void	builtin_cd(t_shell *shell, char **args)
{
	char	*dir;
	char	old_pwd[1024];
	int		is_dash;

	is_dash = is_cd_dash(args);
	if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
		old_pwd[0] = '\0';
	dir = get_cd_target(shell, args);
	if (!dir || change_directory(dir))
	{
		shell->exit_status = 1;
		return ;
	}
	update_cd_env(shell, old_pwd);
	if (is_dash)
		printf("%s\n", get_env_value(shell, "PWD"));
	shell->exit_status = 0;
}
