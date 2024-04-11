/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:12:16 by lle-pier          #+#    #+#             */
/*   Updated: 2024/04/10 18:07:17 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	my_env(char **env, int num)
{
	int	i;
	int	j;

	i = 0;
	if (num == 1)
	{
		while (env[i] != NULL)
		{
			printf("%s\n", env[i]);
			i++;
		}
	}
	else
	{
		while (env[i] != NULL)
		{
			printf("declare -x ");
			j = -1;
			while (env[i][++j] && env[i][j] != '=')
			{
				printf("%c", env[i][j]);
			}
			printf("=\"");
			while (env[i][++j])
			{
				printf("%c", env[i][j]);
			}
			printf("\"\n");
			i++;
		}
	}
}

void	my_echo(char **cmd, t_data *da)
{
	bool	newline;
	int		i;

	i = 1;
	if (ft_strncmp(da->args[0][1], "$?", 2) == 0)
	{
		printf("%i\n", da->exit_status);
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

void	my_cd(char **cmd, char **envp, t_data *da)
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
		da->exit_status = 1;
		return ;
	}
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
	while (da->my_env[i] != NULL)
	{
		if (ft_strncmp(da->my_env[i], da->cmd1[1], ft_strlen(da->cmd1[1])) != 0)
		{
			new_env[j] = ft_strdup(da->my_env[i]);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	free(da->my_env);
	da->my_env = new_env;
	da->exit_status = 0;
}
