/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_check_builtins.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:33:51 by lle-pier          #+#    #+#             */
/*   Updated: 2024/06/03 14:19:06 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_free(t_data *da)
{
	long long	i;
	long long	j;

	i = 0;
	j = 0;
	while (da->my_env[i] != NULL)
	{
		free(da->my_env[i]);
		i++;
	}
	free(da->my_env);
	i = 0;
	if (da->cmd1[1] != NULL)
	{
		while (da->cmd1[1][i])
		{
			if ((da->cmd1[1][i] > 47 && da->cmd1[1][i] < 58) \
			|| da->cmd1[1][i] == '-' || da->cmd1[1][i] == '+')
				j++;
			i++;
		}
	}
	free_cmd(da);
	exit_number(da, i, j);
}

int	check_extern_builtins(t_data *da, char **envp, int index)
{
	size_t	size;
	int		i;

	i = 0;
	if (!da->args[0][0])
		return (0);
	size = ft_strlen(da->args[0][0]);
	if (size == 4 && ft_strchr(da->args[0][0], "exit") && da->pnum == 1)
		if (exit_case(da, index, envp) == 1)
			return (1);
	if (size == 5 && ft_strchr(da->args[0][0], "unset"))
		if (unset_case(da, index, i, envp) == 1)
			return (1);
	if (ft_strchr(da->args[0][0], "export") && size == 6 && \
	da->pnum == 1 && da->args_tab[0][0] != NULL)
		if (export_case(da, index, envp) == 1)
			return (1);
	if (ft_strchr(da->args[0][0], "cd") && size == 2 && da->pnum == 1)
		if (cd_case(da, index, envp) == 1)
			return (1);
	return (0);
}

int	check_unset_echo_export(t_data *da, int index, size_t size)
{
	if (size == 5 && ft_strchr(da->cmd1[0], "unset"))
	{
		outfile_error(da, index, 0);
		if (da->cmd1[1] == NULL)
			return (1);
		if (da->pnum == 1)
			return (my_unset(da, 1), free_cmd(da), 1);
		return (1);
	}
	if (size == 6 && ft_strchr(da->cmd1[0], "export"))
	{
		outfile_error(da, index, 0);
		if (da->cmd1[1] == NULL)
			return (sort_env(da), free_cmd(da), 1);
		return (1);
	}
	if (size == 4 && ft_strchr(da->cmd1[0], "echo"))
	{
		outfile_error(da, index, 0);
		return (my_echo(da->cmd1, 1, 0, 0), free_cmd(da), 1);
	}
	return (0);
}

int	check_more_builtins(t_data *da, int index, size_t size)
{
	if (size == 3 && ft_strchr(da->cmd1[0], "pwd"))
	{
		outfile_error(da, index, 0);
		if (da->cmd1[1] && da->cmd1[1][0] == '-')
			write(2, "pwd: invalid option\n", 20);
		else
			return (my_pwd(), free_cmd(da), 1);
		return (1);
	}
	if (size == 3 && ft_strchr(da->cmd1[0], "env"))
	{
		if (da->cmd1[1] != NULL)
		{
			write(2, "env: bad option ", 16);
			write(2, da->cmd1[1], ft_strlen(da->cmd1[1]));
			return (write(2, "\n", 1), 1);
		}
		outfile_error(da, index, 0);
		return (my_env(da->my_env, 1), free_cmd(da), 1);
	}
	if (size == 2 && ft_strchr(da->cmd1[0], "cd"))
		return (outfile_error(da, index, 0), 1);
	return (0);
}

int	check_builtins(t_data *da, int index)
{
	size_t	size;

	size = ft_strlen(da->cmd1[0]);
	if (size == 4 && ft_strchr(da->cmd1[0], "exit"))
	{
		outfile_error(da, index, 0);
		if (da->cmd1[1] && da->cmd1[2] != NULL)
		{
			write(2, "minishell: exit: too many arguments\n", 36);
			exit (1);
		}
		if (da->cmd1[1] != NULL)
			exit(ft_atoi(da->cmd1[1]));
		exit(da->exit_status);
	}
	if (check_unset_echo_export(da, index, size) == 1)
		return (1);
	if (check_more_builtins(da, index, size) == 1)
		return (1);
	return (0);
}
