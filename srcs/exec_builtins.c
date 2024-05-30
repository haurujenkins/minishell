/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:12:16 by lle-pier          #+#    #+#             */
/*   Updated: 2024/05/30 17:27:06 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	my_env(char **env, int num)
{
	int	i;
	int	k;

	i = -1;
	if (num == 1)
	{
		while (env[++i] != NULL)
		{
			k = 0;
			while (env[i][k])
			{
				if (env[i][k] == '=')
					break ;
				k++;
			}
			if (env[i][k] == '=')
				printf("%s\n", env[i]);
		}
	}
	else
	{
		print_export(env, -1, -1);
	}
}

int	my_echo(char **cmd, int i, int j, int flag)
{
	bool	newline;

	newline = true;
	if (!cmd[1])
		return (printf("\n"), 1);
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], "-n") == 1)
			echo_option(&newline, cmd, i, &flag);
		else
		{
			if (i > 1 && j == 0)
				printf(" ");
			j = 0;
			printf("%s", cmd[i]);
			if (i == 1)
				newline = true;
			flag = 1;
		}
		i++;
	}
	if (newline && !ft_strchr(cmd[1], "\n"))
		printf("\n");
	return (0);
}

void	my_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		write(2, "Error: pwd failed\n", 19);
		exit(1);
	}
	if (pwd)
	{
		printf("%s\n", pwd);
		free(pwd);
	}
	else
		printf("\n");
}

int	my_cd(char **cmd, char **envp, t_data *da)
{
	char		*path;
	struct stat	sb;

	if (!cmd[1] || ft_strchr(cmd[1], "~") == 1)
	{
		path = get_home(envp);
		if (!path)
			return (write(2, "cd: HOME not set\n", 17), da->exit_status = 1, 1);
	}
	else
	{
		path = ft_strdup(cmd[1]);
		if (!path)
			return (write(2, "malloc fail\n", 13), da->exit_status = 134, 1);
	}
	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
	{
		if (cd_error(path, da) == 1)
			return (1);
	}
	else
		return (free(path), write(2, "cd: not a directory \n", 21), \
		da->exit_status = 1, 1);
	free_cmd(da);
	return (free(path), da->exit_status = 0, 0);
}

int	my_unset(t_data *da, int k)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	new_env = malloc(sizeof(char *) * (ft_tablen(da->my_env) + 1));
	if (!new_env)
		return (write(2, "malloc err\n", 11), da->exit_status = 134, 1);
	while (da->my_env[i] != NULL)
	{
		if (ft_strncmp(da->my_env[i], da->cmd1[k], ft_strlen(da->cmd1[k])) != 0)
		{
			new_env[j] = ft_strdup(da->my_env[i]);
			if (!new_env[j])
				return (write(2, "malloc err\n", 11), da->exit_status = 134, 1);
			j++;
		}
		free(da->my_env[i]);
		i++;
	}
	new_env[j] = NULL;
	free(da->my_env);
	da->my_env = new_env;
	return (da->exit_status = 0, 0);
}
