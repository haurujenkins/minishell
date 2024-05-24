/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_check_builtins.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:33:51 by lle-pier          #+#    #+#             */
/*   Updated: 2024/05/23 16:04:07 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_free(t_data *da)
{
	size_t	i;
	size_t	j;

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
	if (i == j && i > 0 && j > 0)
	{
		i = ft_atoi(da->cmd1[1]);
		if (j > 2 && i == 0)
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
		free_struct(da);
		exit(2);
	}
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
	{
		if (outfile_extern_error(da, index, 0) == 1)
			return (1);
		if (get_args_builtins(da, index) == 1)
			return (1);
		if (da->cmd1[1] && da->cmd1[2] != NULL)
		{
			da->exit_status = 1;
			return (write(2, "exit \nminishell: exit: too many arguments\n", 42), 1);
		}
		exit_free(da);
	}
	if (size == 5 && ft_strchr(da->args[0][0], "unset"))
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
			return (1);
		}
	}
	if (ft_strchr(da->args[0][0], "export") && size == 6 && \
	da->pnum == 1 && da->args_tab[0][0] != NULL)
	{
		if (outfile_extern_error(da, index, 0) == 1)
			return (1);
		if (get_args_builtins(da, index) == 1)
			return (1);
		return (my_export(da), 1);
	}
	if (ft_strchr(da->args[0][0], "cd") && size == 2 && da->pnum == 1)
	{
		if (outfile_extern_error(da, index, 0) == 1)
			return (1);
		if (get_args_builtins(da, index) == 1)
			return (1);
		if (da->cmd1[1] && da->cmd1[2] != NULL)
		{
			da->exit_status = 1;
			return (write(2, " too many arguments\n", 20), 1);
		}
		return (my_cd(da->cmd1, envp, da), 1);
	}
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
	if (size == 5 && ft_strchr(da->cmd1[0], "unset"))
	{
		outfile_error(da, index, 0);
		if (da->cmd1[1] == NULL)
			return (1);
		if (da->pnum == 1)
			return (my_unset(da, 1), 1);
		return (1);
	}
	if (size == 6 && ft_strchr(da->cmd1[0], "export"))
	{
		outfile_error(da, index, 0);
		if (da->cmd1[1] == NULL)
			return (sort_env(da), 1);
		return (1);
	}
	if (size == 4 && ft_strchr(da->cmd1[0], "echo"))
	{
		outfile_error(da, index, 0);
		return (my_echo(da->cmd1), 1);
	}
	if (size == 3 && ft_strchr(da->cmd1[0], "pwd"))
	{
		outfile_error(da, index, 0);
		if (da->cmd1[1] && da->cmd1[1][0] == '-')
			write(2, "pwd: invalid option\n", 20);
		else
			return (my_pwd(), 1);
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
		return (my_env(da->my_env, 1, 0), 1);
	}
	if (size == 2 && ft_strchr(da->cmd1[0], "cd"))
	{
		outfile_error(da, index, 0);
		return (1);
	}
	return (0);
}
