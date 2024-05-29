/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export_oldpwd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:16:55 by lle-pier          #+#    #+#             */
/*   Updated: 2024/05/29 11:29:55 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	old_pwd(t_data *da, int i, char *temp, char *cmd)
{
	while (da->my_env[i])
	{
		if (ft_strchr(da->my_env[i], "OLDPWD") == 1)
		{
			cmd = ft_strdup("OLDPWD");
			free(da->my_env[i]);
			da->my_env[i] = ft_strjoin_ori(cmd, temp);
			free(temp);
			da->check_export = 1;
			return ;
		}
		i++;
	}
}

void	export_pwd(t_data *da, char *temp_value)
{
	int		i;
	char	*temp;
	char	*cmd;

	i = 0;
	while (da->my_env[i])
	{
		if (ft_strchr(da->my_env[i], "PWD") == 1)
		{
			cmd = ft_strdup("PWD=");
			temp = ft_strdup(da->my_env[i] + 3);
			free(da->my_env[i]);
			da->my_env[i] = ft_strjoin_ori(cmd, temp_value);
		}
		i++;
	}
	old_pwd(da, 0, temp, cmd);
}
