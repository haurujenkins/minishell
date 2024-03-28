/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:12:16 by lle-pier          #+#    #+#             */
/*   Updated: 2024/03/27 18:12:39 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	my_echo(char **cmd)
{
	bool	newline;
	int		i;

	i = 1;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], "-n") == 1 && i == 1)
			newline = false;
		else
		{
			if (newline && i > 1)
				printf(" ");
			printf("%s", cmd[i]);
			newline = true;
		}
		i++;
	}
	if (newline)
		printf("\n");
}

void	my_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
}

void	my_cd(char **cmd, char **envp)
{
	char	*path;

	if (!cmd[1] || ft_strchr(cmd[1], "~") == 1)
	{
		path = get_home(envp);
		if (!path)
			return ;
	}
	else
		path = cmd[1];
	if (chdir(path) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", path);
		free(path);
		return ;
	}
	free(path);
}

void	my_env(t_data *da)
{
	int		i;

	i = 0;
	while (da->my_env[i] != NULL)
	{
		printf("%s\n", da->my_env[i]);
		i++;
	}
}

int	check_extern_builtins(t_data *da, char **envp, int index)
{
	if (ft_strchr(da->args[0][0], "cd") && da->pnum == 1)
	{
		get_args(da, envp, index);
		return (my_cd(da->cmd1, envp), 1);
	}
	return (0);
}

int	check_builtins(t_data *da)
{
	if (ft_strchr(da->cmd1[0], "echo"))
		return (my_echo(da->cmd1), 1);
	if (ft_strchr(da->cmd1[0], "pwd"))
	{
		if (da->cmd1[1] != NULL)
		{
			printf("pwd: bad option %s\n", da->cmd1[1]);
			return (1);
		}
		else
			return (my_pwd(), 1);
	}
	if (ft_strchr(da->cmd1[0], "env"))
	{
		if (da->cmd1[1] != NULL)
		{
			printf("env: bad option %s\n", da->cmd1[1]);
			return (1);
		}
		else
			return (my_env(da), 1);
	}
	return (0);
}
