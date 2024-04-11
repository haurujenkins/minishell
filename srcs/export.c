/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:37:46 by lle-pier          #+#    #+#             */
/*   Updated: 2024/04/11 11:07:57 by lle-pier         ###   ########.fr       */
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

void	export_var(t_data *da, char *temp_cmd, char *temp_value, int i)
{
	while (da->my_env[i] != NULL)
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

	i = 0;
	da->check_export = 0;
	if (da->cmd1[1] != NULL)
	{
		while (da->cmd1[1][i] != '=')
			i++;
		temp_cmd = malloc(sizeof(char) * (i + 1));
		ft_strlcpy(temp_cmd, da->cmd1[1], i + 2);
		temp_value = malloc(sizeof(char) * (ft_strlen(da->cmd1[1]) - i + 1));
		ft_strlcpy(temp_value, da->cmd1[1] + i + 1, ft_strlen(da->cmd1[1]) - i);
		export_var(da, temp_cmd, temp_value, i);
		if (da->check_export == 0)
		{
			da->my_env = ft_realloc(da->my_env, sizeof(char *) \
			* (ft_tablen(da->my_env) + 2));
			da->my_env[ft_tablen(da->my_env)] = \
			ft_strjoin_ori(temp_cmd, temp_value);
			da->my_env[ft_tablen(da->my_env) + 1] = NULL;
			free(temp_value);
		}
	}
	da->exit_status = 1;
}
