/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:37:46 by lle-pier          #+#    #+#             */
/*   Updated: 2024/04/22 11:49:29 by lle-pier         ###   ########.fr       */
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
	while (da->my_env[i] != NULL)
	{
		dup_env[i] = ft_strdup(da->my_env[i]);
		i++;
	}
	dup_env[i] = NULL;
	sort_tab(dup_env);
	my_env(dup_env, 2);
	i = 0;
	while (dup_env[i] != NULL)
	{
		i++;
		free(dup_env[i]);
		dup_env[i] = NULL;
	}
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

void	my_export(t_data *da)
{
	char	*temp_cmd;
	char	*temp_value;
	int		i;
	int		k;

	k = 1;
	while (da->cmd1[k] != NULL)
	{
		i = 0;
		da->check_export = 0;
		if (da->cmd1[k][0] == '=' && ft_strlen(da->cmd1[k]) == 1)
		{
			write(2, " not a valid identifier\n", 24);
			da->exit_status = 1;
			return ;
		}
		if (da->cmd1[k][0] > 47 && da->cmd1[k][0] < 58)
		{
			write(2, " not a valid identifier\n", 24);
			da->exit_status = 1;
			return ;
		}
		while (da->cmd1[k][i] != '=')
		{
			if (da->cmd1[k][i] == '-')
			{
				write(2, " not a valid identifier\n", 24);
				da->exit_status = 1;
				return ;
			}
			else if (da->cmd1[k][i] == '\0')
				break ;
			else if (da->cmd1[k][i] == ' ')
			{
				i++;
				printf("export: %s: not a valid identifier\n", da->cmd1[k]);
				da->exit_status = 0;
				return ;
			}
			i++;
		}
		temp_cmd = malloc(sizeof(char) * (i + 1));
		ft_strlcpy(temp_cmd, da->cmd1[k], i + 1);
		temp_value = malloc(sizeof(char) * (ft_strlen(da->cmd1[k]) - i + 1));
		if (da->cmd1[k][i] == '\0' || da->cmd1[k][i] == ' ')
		{
			ft_strlcpy(temp_value, "", 1);
		}
		else
		{
			ft_strlcpy(temp_value, da->cmd1[k] + i, \
			ft_strlen(da->cmd1[k]) - i + 1);
		}
		export_var(da, temp_cmd, temp_value);
		if (da->check_export == 0)
		{
			i = ft_tablen(da->my_env);
			da->my_env = ft_realloc(da->my_env, sizeof(char *) \
			* (i + 2));
			i = ft_tablen(da->my_env);
			da->my_env[i] = \
			ft_strjoin_ori(temp_cmd, temp_value);
			da->my_env[i + 1] = NULL;
			free(temp_value);
		}
		k++;
	}
	k = 0;
	while (da->cmd1[k] != NULL)
	{
		free(da->cmd1[k]);
		k++;
	}
	free(da->cmd1);
	da->cmd1 = NULL;
	da->exit_status = 0;
}
