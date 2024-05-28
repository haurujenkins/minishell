/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:52:12 by lle-pier          #+#    #+#             */
/*   Updated: 2024/05/28 17:22:20 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cd_error(char *path, t_data *da)
{
	char		*cwd;

	if (chdir(path) == -1)
		return (perror("chdir"), free(path), da->exit_status = 1, 1);
	else
	{
		cwd = getcwd(NULL, 0);
		if (cwd)
		{
			export_pwd(da, cwd);
			free(cwd);
		}
		else
			return (perror("getcwd"), free(path), da->exit_status = 1, 1);
	}
	return (0);
}

int	check_unset(t_data *da, int k)
{
	int	i;

	i = 0;
	while (da->cmd1[k][i] != '\0')
	{
		if (da->cmd1[k][i] == ' ' || da->cmd1[k][i] == '-' || \
		da->cmd1[k][i] == '+' || da->cmd1[k][i] == '%' || da->cmd1[k][i] \
		== '!' || da->cmd1[k][i] == '@' || da->cmd1[k][i] == '#' || \
		da->cmd1[k][i] == '^' || da->cmd1[k][i] == ':' || da->cmd1[k][i] \
		== '?' || da->cmd1[k][i] == ',' || da->cmd1[k][i] == '.' || \
		da->cmd1[k][i] == '/' || da->cmd1[k][i] == '\\' || da->cmd1[k][i] \
		== '|' || da->cmd1[k][i] == '`' || da->cmd1[k][i] == '~' || \
		da->cmd1[k][i] == '}' || da->cmd1[k][i] == '{' || \
		da->cmd1[k][i] == '*')
		{
			write(2, "unset: `", 8);
			write(2, da->cmd1[k], ft_strlen(da->cmd1[k]));
			write(2, "' : not a valid identifier\n", 27);
			da->exit_status = 0;
			return (1);
		}
		i++;
	}
	return (0);
}

void	print_export(char **env, int i, int j)
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

void	echo_option(bool *newline, char **cmd, int i, int *flag)
{
	int	j;

	j = 1;
	while (cmd[i][j])
	{
		if (cmd[i][j] != 'n')
		{
			*flag = 1;
			if (i == 1)
				*newline = true;
			j = 0;
			break ;
		}
		else
			if (i == 1)
				*newline = false;
		j++;
	}
	if (*flag == 1)
	{
		if (i > 1)
			printf(" ");
		printf("%s", cmd[i]);
	}
}
