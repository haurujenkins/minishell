/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cpy_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:14:05 by abolea            #+#    #+#             */
/*   Updated: 2024/05/29 17:16:01 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*args_before(t_data *da, char **words, char *args)
{
	if ((words[da->i_args][0] == '<' || words[da->i_args][0] == '>') || (words[da->i_args - 1][0] == '<' || words[da->i_args - 1][0] == '>'))
		da->i_args++;
	else if ((words[da->i_args][0] != '<' && words[da->i_args][0] != '>') && (words[da->i_args - 1][0] != '<' && words[da->i_args - 1][0] != '>'))
	{
		args = ft_strjoin_ori(args, words[da->i_args]);
		if (!args)
			return (NULL);
		if (da->s_args != 1)
			args = cpy_args_without_quotes(args);
		if (!args)
			return (NULL);
		da->i_args++;
		return (args);
	}
	return (NULL);
}

char	*else_args_before_quotes(t_data *da, char **words, char *args, int i)
{
	while ((words[da->i_args] && (words[da->i_args][0] != '<' && words[da->i_args][0] != '>')))
	{	
		args = ft_strjoin_ori(args, words[da->i_args]);
		if (!args)
			return (NULL);
		if (words[da->i_args + 1] && (words[da->i_args + 1][0] != '<' && words[da->i_args + 1][0] != '>'))
		{
			args = ft_strjoin_ori(args, " ");
			if (!args)
				return (NULL);
		}
		da->i_args++;
	}
	if (ft_strncmp(da->args[i][0], "export", 6) != 0)
	{
		args = cpy_args_without_quotes(args);
		if (!args)
			return (NULL);
	}
	da->i_args++;
	return (args);
}

char	*else_args_before(t_data *da, char **words, char *args)
{
	args = ft_strjoin_ori(args, words[da->i_args]);
	if (!args)
		return (NULL);
	if (da->s_args != 1)
		args = cpy_args_without_quotes(args);
	if (!args)
		return (NULL);
	da->i_args++;
	return (args);
}

char	*if_args_before_ok(t_data *da, char **words, char *args, int i)
{
	args = args_before(da, words, args);
	if (args)
		return (args);
	else
	{
		if (if_quotes(words[da->i_args], 0) == 1)
		{
			args = else_args_before_quotes(da, words, args, i);
			if (args)
				return (args);
		}
		else
		{
			args = else_args_before(da, words, args);
			if (args)
				return (args);
		}
	}
	return (NULL);
}

char	*if_args_after_ok(t_data *da, char **words, char *args)
{
	args = args_after(da, words, args);
	if (args)
		return (args);
	args = else_args_after(da, words, args);
	if (args)
		return (args);
	return (NULL);
}
