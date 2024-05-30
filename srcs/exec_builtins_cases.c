/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins_cases.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:20:38 by lle-pier          #+#    #+#             */
/*   Updated: 2024/05/30 14:18:10 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	unset_case(t_data *da, int index, int i)
{
	if (outfile_extern_error(da, index, 0) == 1)
		return (1);
	if (da->args_tab[0][0] == NULL)
		return (0);
	else if (da->pnum == 1)
	{
		get_args_builtins(da, 0);
		while (da->cmd1[++i] != NULL)
		{
			if (check_unset(da, i) == 0)
				my_unset(da, i);
		}
		free_cmd(da);
		return (1);
	}
	return (1);
}

int	exit_case(t_data *da, int index)
{
	if (outfile_extern_error(da, index, 0) == 1)
		return (1);
	if (get_args_builtins(da, index) == 1)
		return (1);
	if (da->cmd1[1] && da->cmd1[2] != NULL)
	{
		da->exit_status = 1;
		write(2, "exit \nminishell: exit: too many arguments\n", 42);
		return (1);
	}
	exit_free(da);
	return (1);
}

int	export_case(t_data *da, int index)
{
	if (outfile_extern_error(da, index, 0) == 1)
		return (1);
	if (get_args_builtins(da, index) == 1)
		return (1);
	return (my_export(da, 0, 1, 0), 1);
}

int	cd_case(t_data *da, int index, char **envp)
{
	if (outfile_extern_error(da, index, 0) == 1)
		return (1);
	if (get_args_builtins(da, index) == 1)
		return (1);
	if (da->cmd1[1] && da->cmd1[2] != NULL)
	{
		da->exit_status = 1;
		write(2, "cd: too many arguments\n", 23);
		return (1);
	}
	return (my_cd(da->cmd1, envp, da), 1);
}

void	exit_number(t_data *da, long long i, long long j)
{
	if (i == j && i > 0 && j > 0)
	{
		i = ft_atoi(da->cmd1[1]);
		if (i > INT_MAX || i < INT_MIN || (j > 2 && i == 0))
		{
			write (2, "bash: exit: ", 12);
			write (2, "numeric argument required\n", 27);
			i = 2;
		}
		free_struct(da);
		write(2, "exit\n", 5);
		exit(i);
	}
	else
	{
		if (i > 0)
		{
			write(2, "exit\n", 5);
			write(2, "minishell: exit: numeric argument required\n", 43);
		}
		else
			write(2, "exit\n", 5);
		free_cmd_notfound(da);
		exit(2);
	}
}
