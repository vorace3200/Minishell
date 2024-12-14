/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:42:39 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/14 14:22:00 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

void	builtin_cd(t_shell *shell, char **args)
{
	char	*dir;
	char	cwd[1024];

	if (args[1] != NULL)
		dir = args[1];
	else
		dir = get_env_value(shell, "HOME");
	if (!dir)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		shell->exit_status = 1;
		return ;
	}
	if (chdir(dir) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(dir, 2);
		ft_putstr_fd(": not a directory\n", 2);
		shell->exit_status = 1;
		return ;
	}
	if (getcwd(cwd, sizeof(cwd)))
		set_env_value(shell, "PWD", cwd);
	shell->exit_status = 0;
}
