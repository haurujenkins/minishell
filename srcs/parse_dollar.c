/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:20:22 by lle-pier          #+#    #+#             */
/*   Updated: 2024/04/17 10:51:33 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	len_after_dollar(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '$')
		i++;
	while (ft_isalnum(s[i]) == 1)
	{
		i++;
		j++;
	}
	return (j);
}

char	*after_dollar(char *s)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;

	i = 0;
	j = 0;
	if (if_dollar(s) == 0)
		return (NULL);
	len = len_after_dollar(s);
	tmp = malloc((len + 1) * sizeof(char) + 150);
	while (s[i] != '$')
		i++;
	i++;
	while (ft_isalnum(s[i]) == 1)
	{
		tmp[j] = s[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

char	*temp_without_dollar(t_data *da, char *temp_args)
{
	int		i;
	int		j;
	int		k;
	int		len;
	char	*new_args;
	char	*before_args;
	char	*res;

	i = 0;
	j = 0;
	k = 0;
	before_args = after_dollar(temp_args);
	if (before_args == NULL)
		return (temp_args);
	new_args = find_in_env(da, before_args);
	while (temp_args[i])
	{
		if (temp_args[i] == '$' && temp_args[i + 1])
		{
			while (temp_args[i] != '\0' && temp_args[i] != ' ')
			{
				i++;
			}
		}
		j++;
		i++;
	}
	len = (j + ft_strlen(new_args) + 1);
	res = malloc(len * sizeof(char));
	i = 0;
	j = 0;
	while (temp_args[i] != '$')
	{
		res[j] = temp_args[i];
		i++;
		j++;
	}
	while (new_args[k])
	{
		res[j] = new_args[k];
		j++;
		k++;
	}
	while (temp_args[i] != '\0')
	{
		if (temp_args[i] == '$' && temp_args[i + 1])
		{
			while (temp_args[i] != '\0' && temp_args[i] != ' ')
			{
				i++;
			}
		}
		res[j] = temp_args[i];
		i++;
		j++;
	}
	res[j] = '\0';
	return (res);
}
