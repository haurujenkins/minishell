/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:28:04 by abolea            #+#    #+#             */
/*   Updated: 2024/06/07 12:50:15 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*cpy_args_without_s_quotes(char *s)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = malloc((ft_strlen(s) - nb_quotes(s) + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	while (s[i])
	{
		if (s[i] == 39)
			i++;
		tmp[j] = s[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	free (s);
	return (tmp);
}

char	*cpy_until_char(char *s, char c, int start)
{
	char	*tmp;
	int		j;
	int		len;

	j = 0;
	len = ft_strlen(s);
	tmp = malloc((len - start + 1) * sizeof(char));
	if (!tmp)
		return (write(2, "Malloc failed\n", 14), NULL);
	while (s[start] != c && start < len)
	{
		tmp[j] = s[start];
		start++;
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

int	len_for_args(char *s, int start)
{
	int		j;
	int		len;

	j = 0;
	len = ft_strlen(s);
	while ((s[start] != '<' && s[start] != '>' \
	&& s[start] != ' ') && start < len)
	{
		j++;
		start++;
	}
	return (j);
}

char	*cpy_for_args(char *s, int start)
{
	char	*tmp;
	int		j;
	int		len;

	j = 0;
	len = len_for_args(s, start);
	tmp = malloc((len - start + 1) * sizeof(char));
	if (!tmp)
		return (write(2, "Malloc failed\n", 14), NULL);
	while ((s[start] != '<' && s[start] != '>' \
	&& s[start] != ' ') && start < len)
	{
		tmp[j] = s[start];
		start++;
		j++;
	}
	tmp[j] = '\0';
	free (s);
	return (tmp);
}
