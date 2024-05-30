/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export_errors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:27:28 by lle-pier          #+#    #+#             */
/*   Updated: 2024/05/30 15:08:42 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	export_errors(t_data *da, int k)
{
	da->check_export = 0;
	if ((da->cmd1[k][0] == '=' || da->cmd1[k][0] == '%') && \
	ft_strlen(da->cmd1[k]) == 1)
	{
		write(2, "export: `", 9);
		write(2, da->cmd1[k], ft_strlen(da->cmd1[k]));
		write(2, "' : not a valid identifier\n", 27);
		da->exit_status = 1;
		return (0);
	}
	if (da->cmd1[k][0] > 47 && da->cmd1[k][0] < 58)
	{
		write(2, "export: `", 9);
		write(2, da->cmd1[k], ft_strlen(da->cmd1[k]));
		write(2, "' : not a valid identifier\n", 27);
		da->exit_status = 1;
		return (0);
	}
	return (1);
}

int	char_error_export(t_data *da, int k, int i)
{
	if (da->cmd1[k][i] == ' ' || da->cmd1[k][i] == '-' || \
	da->cmd1[k][i] == '+' || da->cmd1[k][i] == '%' || da->cmd1[k][i] \
	== '!' || da->cmd1[k][i] == '@' || da->cmd1[k][i] == '#' || \
	da->cmd1[k][i] == '^' || da->cmd1[k][i] == ':' || da->cmd1[k][i] \
	== '?' || da->cmd1[k][i] == ',' || da->cmd1[k][i] == '.' || \
	da->cmd1[k][i] == '/' || da->cmd1[k][i] == '\\' || da->cmd1[k][i] \
	== '|' || da->cmd1[k][i] == '`' || da->cmd1[k][i] == '~' || \
	da->cmd1[k][i] == '}' || da->cmd1[k][i] == '{' ||
	da->cmd1[k][i] == '*')
	{
		write(2, "export: `", 9);
		write(2, da->cmd1[k], ft_strlen(da->cmd1[k]));
		write(2, "' : not a valid identifier\n", 27);
		da->exit_status = 0;
		return (1);
	}
	return (0);
}

int	while_not_equal(t_data *da, int k, int i)
{
	if ((da->cmd1[k][0] == '=' || da->cmd1[k][0] == '\0') && i == 0)
	{
		i++;
		printf("export: %s: not a valid identifier\n", da->cmd1[k]);
		da->exit_status = 0;
		return (0);
	}
	if (da->cmd1[k][i] == '-' && i == 0)
	{
		printf("export: -%c : invalid option\n", da->cmd1[k][1]);
		da->exit_status = 1;
		return (0);
	}
	else if (da->cmd1[k][i] == '\0')
		return (1);
	else if (char_error_export(da, k, i) == 1)
		return (0);
	return (2);
}

void	check_export_zero(t_data *da, int i, char *temp_cmd, char *temp_value)
{
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
}
