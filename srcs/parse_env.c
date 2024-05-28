/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:20:49 by lle-pier          #+#    #+#             */
/*   Updated: 2024/05/28 11:00:12 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	len_env(t_data *da, char *s)
{
	int		i;
	int		j;
	int		l;

	i = 0;
	j = 0;
	l = 0;
	while (da->my_env[i] != NULL)
	{
		if (ft_strncmp(da->my_env[i], s, ft_strlen(s)) != 0)
		{
			while (da->my_env[i][j] != '=')
				j++;
			j++;
			while (da->my_env[i][j])
			{
				j++;
				l++;
			}
			if (l != 0)
				return (l);
		}
		i++;
	}
	return (0);
}

int	len_before_equal(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '=')
		i++;
	return (i);
}

char	*find_in_env(t_data *da, char *s)
{
	int		i;
	int		j;
	int		l;
	int		len;
	char	*res;

	i = 0;
	j = 0;
	l = 0;
	len = ft_tablen(da->my_env);
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (da->my_env[i] != NULL)
	{
		if (ft_strncmp(da->my_env[i], s, len_before_equal(da->my_env[i])) == 0)
		{
			while (da->my_env[i][j] != '=')
			{
				if (da->my_env[i][j] == '\0')
					return ("\n");
				j++;
			}
			j++;
			while (da->my_env[i][j])
			{
				res[l] = da->my_env[i][j];
				j++;
				l++;
			}
			if (res)
			{
				res[l] = '\0';
				return (res);
			}
		}
		i++;
	}
	res[0] = '\0';
	free (s);
	return (res);
}
