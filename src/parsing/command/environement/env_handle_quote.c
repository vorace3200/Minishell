/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handle_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 00:17:58 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/19 00:43:07 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Minishell.h"

char	*expand_variable(t_shell *shell, const char *arg, int *index)
{
	char	*var_name;
	char	*value;
	int		start;
	char	*env_val;

	(*index)++;
	var_name = get_var_name(&arg[*index], &start);
	*index += start;
	if (!var_name)
		return (NULL);
	if (ft_strcmp(var_name, "?") == 0)
		value = ft_itoa(shell->exit_status);
	else
	{
		env_val = get_env_value(shell, var_name);
		if (!env_val)
			value = ft_strdup("");
		else
			value = ft_strdup(env_val);
	}
	if (!value)
		value = ft_strdup("");
	free(var_name);
	return (value);
}

void	fdp_quotes(const char c, int *in_single, int *in_double)
{
	if (c == '\'')
		*in_single = !(*in_single);
	else if (c == '"')
		*in_double = !(*in_double);
}

static char	*process_char_with_quotes(t_quote_process *data)
{
	char	tmp[2];
	char	*expanded;

	if (data->arg[*(data->i)] == '$' && !data->in_single && data->arg[*(data->i)
			+ 1] && (ft_isalnum(data->arg[*(data->i) + 1])
			|| data->arg[*(data->i)
				+ 1] == '_' || data->arg[*(data->i) + 1] == '?'))
	{
		expanded = expand_variable(data->shell, data->arg, data->i);
		*(data->res) = ft_strjoin_free(*(data->res), expanded);
		free(expanded);
		return (NULL);
	}
	tmp[0] = data->arg[*(data->i)];
	tmp[1] = '\0';
	*(data->res) = ft_strjoin_free(*(data->res), tmp);
	return (*(data->res));
}

char	*process_char(t_shell *shell, const char *arg, int *i, char **res)
{
	static int		in_single;
	static int		in_double;
	t_quote_process	data;

	if ((arg[*i] == '\'' && !in_double) || (arg[*i] == '\"' && !in_single))
		fdp_quotes(arg[*i], &in_single, &in_double);
	else
	{
		data.shell = shell;
		data.arg = arg;
		data.i = i;
		data.res = res;
		data.in_single = in_single;
		return (process_char_with_quotes(&data));
	}
	return (*res);
}
