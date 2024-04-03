/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:12:16 by lle-pier          #+#    #+#             */
/*   Updated: 2024/04/03 16:25:03 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_realloc(char **tab, int size)
{
	char	**new_tab;
	int		i;

	i = 0;
	new_tab = malloc(size);
	while (tab[i] != NULL)
	{
		new_tab[i] = malloc(sizeof(char) * (ft_strlen(tab[i]) + 1));
		ft_strlcpy(new_tab[i], tab[i], ft_strlen(tab[i]) + 1);
		i++;
	}
	new_tab[i] = NULL;
	free(tab);
	return (new_tab);
}

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

void	my_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		i++;
		free(env[i]);
		env[i] = NULL;
	}
	free(env);
	env = NULL;
}

void	sort_env(t_data *da)
{
	int		i;
	int		j;
	char	*temp;
	char	**dup_env;

	i = 0;
	dup_env = NULL;
	dup_env = malloc(sizeof(char *) * (ft_tablen(da->my_env) + 1));
	while (da->my_env[i] != NULL)
	{
		dup_env[i] = ft_strdup(da->my_env[i]);
		i++;
	}
	dup_env[i] = NULL;
	i = 0;
	while (dup_env[i] != NULL)
	{
		j = i + 1;
		while (dup_env[j] != NULL)
		{
			if (ft_strncmp(dup_env[i], dup_env[j], ft_strlen(dup_env[i])) > 0)
			{
				temp = dup_env[i];
				dup_env[i] = dup_env[j];
				dup_env[j] = temp;
			}
			j++;
		}
		i++;
	}
	my_env(dup_env);
	free_env(dup_env);
}

void	my_export(t_data *da)
{
	char	*temp_cmd;
	char	*temp_value;
	int		i;
	int		check;

	i = 0;
	check = 0;
	if (da->cmd1[1] == NULL)
	{
		sort_env(da);
		return ;
	}
	while (da->cmd1[1][i] != '=')
		i++;
	temp_cmd = malloc(sizeof(char) * (i + 1));
	ft_strlcpy(temp_cmd, da->cmd1[1], i + 2);
	temp_value = malloc(sizeof(char) * (ft_strlen(da->cmd1[1]) - i + 1));
	ft_strlcpy(temp_value, da->cmd1[1] + i + 1, ft_strlen(da->cmd1[1]) - i);
	while (da->my_env[i] != NULL)
	{
		if (ft_strchr(da->my_env[i], temp_cmd) == 1)
		{
			free(da->my_env[i]);
			da->my_env[i] = ft_strjoin_ori(temp_cmd, temp_value);
			free(temp_value);
			check = 1;
			return ;
		}
		i++;
	}
	if (check == 0)
	{
		da->my_env = ft_realloc(da->my_env, sizeof(char *) * (ft_tablen(da->my_env) + 2));
		da->my_env[ft_tablen(da->my_env)] = ft_strjoin_ori(temp_cmd, temp_value);
		da->my_env[ft_tablen(da->my_env) + 1] = NULL;
	}
}

int	check_extern_builtins(t_data *da, char **envp, int index)
{
	if (ft_strchr(da->args[0][0], "cd") && da->pnum == 1)
	{
		get_args_builtins(da, index);
		return (my_cd(da->cmd1, envp), 1);
	}
	if (ft_strchr(da->args[0][0], "export") && da->pnum == 1)
	{
		get_args_builtins(da, index);
		return (my_export(da), 1);
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
			return (my_env(da->my_env), 1);
	}
	return (0);
}
