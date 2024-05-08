/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:12:16 by lle-pier          #+#    #+#             */
/*   Updated: 2024/05/06 13:31:39 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	my_env(char **env, int num, int j)
{
	int	i;

	i = -1;
	if (num == 1)
		while (env[++i] != NULL)
			printf("%s\n", env[i]);
	else
	{
		while (env[++i] != NULL)
		{
			printf("declare -x ");
			j = -1;
			while (env[i][++j] && env[i][j] != '=')
				printf("%c", env[i][j]);
			if (env[i][j] == '=')
			{
				printf("=\"");
				while (env[i][++j])
					printf("%c", env[i][j]);
				printf("\"\n");
			}
			else
				printf("\n");
		}
	}
}

void	my_echo(char **cmd, t_data *da)
{
	bool	newline;
	int		i;
	int		j;

	i = 1;
	j = 0;
	newline = true;
	if (!cmd[1])
	{
		printf("\n");
		return ;
	}
	if (cmd[i][0] == '$' && !cmd[i][1])
	{
		printf("$\n");
		return ;
	}
	if (ft_strncmp(cmd[i], "$?", 2) == 0)
	{
		printf("%i", da->exit_status);
		while (cmd[i][j] != '?')
			j++;
		while (cmd[i][++j] != '\0')
			printf("%c", cmd[i][j]);
		printf("\n");
		return ;
	}
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
	if (newline && !ft_strchr(cmd[1], "\n"))
		printf("\n");
}

void	my_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		printf("%s\n", pwd);
		free(pwd);
	}
	else
		printf("\n");
}

void	my_cd(char **cmd, char **envp, t_data *da)
{
	char	*path;

	if (!cmd[1] || ft_strchr(cmd[1], "~") == 1)
	{
		path = get_home(envp);
		if (!path)
		{
			da->exit_status = 1;
			write(2, "Error: malloc failed\n", 21);
			return ;
		}
	}
	else
	{
		path = ft_strdup(cmd[1]);
		if (!path)
		{
			da->exit_status = 1;
			write(2, "Error: malloc failed\n", 21);
			return ;
		}
	}
	if (chdir(path) == -1)
	{
		write(2, " No such file or directory\n", 27);
		free(path);
		da->exit_status = 1;
		return ;
	}
	else
		export_pwd(da, getcwd(NULL, 0));
	free(path);
	da->exit_status = 0;
}

void	my_unset(t_data *da)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	new_env = malloc(sizeof(char *) * (ft_tablen(da->my_env) + 1));
	if (!new_env)
	{
		da->exit_status = 1;
		write(2, "Error: malloc failed\n", 21);
		return ;
	}
	get_args_builtins(da, 0);
	while (da->my_env[i] != NULL)
	{
		if (ft_strncmp(da->my_env[i], da->cmd1[1], ft_strlen(da->cmd1[1])) != 0)
		{
			new_env[j] = ft_strdup(da->my_env[i]);
			if (!new_env[j])
			{
				da->exit_status = 1;
				write(2, "Error: malloc failed\n", 21);
				return ;
			}
			j++;
		}
		free(da->my_env[i]);
		i++;
	}
	new_env[j] = NULL;
	free(da->my_env);
	da->my_env = new_env;
	da->exit_status = 0;
}
