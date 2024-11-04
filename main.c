/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 00:28:02 by vorace32          #+#    #+#             */
/*   Updated: 2024/11/04 15:34:01 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/Minishell_exec.h"

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, env);
	main_loop(&shell);
	return (0);
}
