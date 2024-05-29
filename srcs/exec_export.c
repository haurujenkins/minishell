/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:37:46 by lle-pier          #+#    #+#             */
/*   Updated: 2024/05/29 15:55:31 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sort_tab(char **dup_env)
{
	int		i;
	int		j;
	char	*temp;

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
}

void	sort_env(t_data *da)
{
	int		i;
	char	**dup_env;

	i = 0;
	dup_env = NULL;
	dup_env = malloc(sizeof(char *) * (ft_tablen(da->my_env) + 1));
	if (dup_env == NULL)
	{
		perror("malloc");
		exit(127);
	}
	while (da->my_env[i] != NULL)
	{
		dup_env[i] = ft_strdup(da->my_env[i]);
		i++;
	}
	dup_env[i] = NULL;
	sort_tab(dup_env);
	my_env(dup_env, 2);
	i = -1;
	while (dup_env[++i])
		free(dup_env[i]);
	free(dup_env);
	dup_env = NULL;
}

void	export_var(t_data *da, char *temp_cmd, char *temp_value)
{
	int	i;

	i = 0;
	while (da->my_env[i])
	{
		if (ft_strchr(da->my_env[i], temp_cmd) == 1)
		{
			free(da->my_env[i]);
			da->my_env[i] = ft_strjoin_ori(temp_cmd, temp_value);
			free(temp_value);
			da->check_export = 1;
			return ;
		}
		i++;
	}
}

void	export_temp_cmd(t_data *da, int i, int k)
{
	char	*temp_cmd;
	char	*temp_value;

	temp_cmd = malloc(sizeof(char) * (i + 1));
	if (temp_cmd == NULL)
	{
		perror("malloc");
		exit(127);
	}
	ft_strlcpy(temp_cmd, da->cmd1[k], i + 1);
	temp_value = malloc(sizeof(char) * \
	(ft_strlen(da->cmd1[k]) - i + 1));
	if (temp_value == NULL)
	{
		perror("malloc");
		exit(127);
	}
	if (da->cmd1[k][i] == '\0' || da->cmd1[k][i] == ' ')
		ft_strlcpy(temp_value, "", 1);
	else
		ft_strlcpy(temp_value, da->cmd1[k] + i, ft_strlen(da->cmd1[k]) - i + 1);
	export_var(da, temp_cmd, temp_value);
	check_export_zero(da, 0, temp_cmd, temp_value);
}

void	my_export(t_data *da, int i, int k, int return_value)
{
	int		export;

	while (da->cmd1[k] != NULL)
	{
		export = 1;
		if (export_errors(da, k) == 0)
			export = 0;
		while (da->cmd1[k][i] != '=')
		{
			return_value = while_not_equal(da, k, i);
			if (return_value != 2)
			{
				if (return_value == 0)
					export = 0;
				break ;
			}
			i++;
		}
		if (export == 1)
			export_temp_cmd(da, i, k);
		k++;
	}
	k = 0;
	da->exit_status = 0;
	free_cmd(da);
}
