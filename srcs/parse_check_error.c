/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:21:13 by abolea            #+#    #+#             */
/*   Updated: 2024/05/29 15:22:45 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_quote_close(char	*rl)
{
	int	i;
	int	d_quote;
	int	s_quote;

	i = 0;
	d_quote = 1;
	s_quote = 1;
	while (rl[i])
	{
		if (rl[i] == 34 && s_quote > 0)
			d_quote *= -1;
		if (rl[i] == 39 && d_quote > 0)
			s_quote *= -1;
		i++;
	}
	if (d_quote < 0 || s_quote < 0)
		return (-1);
	else
		return (0);
}

int	check_rl_two(char *rl, int i)
{
	if (rl[i] == '|' && rl[i + 1] == '|')
		return (-1);
	if (rl[i] == '<' && rl[i + 1] == '>')
		return (-1);
	else if (rl[i] == '>' && rl[i + 1] == '<')
		return (-1);
	else if (rl[i] == '<' && rl[i + 1] == '<' && rl[i + 2] == '<')
		return (-1);
	else if (rl[i] == '>' && rl[i + 1] == '>' && rl[i + 2] == '>')
		return (-1);
	return (0);
}

int	check_rl(char *rl, int i)
{
	if (check_rl_two(rl, i) == -1)
		return (-1);
	else if (rl[i] == '>' && rl[i + 2] == '>')
		return (-1);
	else if (rl[i] == '<' && rl[i + 2] == '<')
		return (-1);
	else if (rl[i] == '|' && rl[i + 1] == '|' && rl[i + 2] == '|')
		return (-1);
	else if (rl[i] == '|')
	{
		i++;
		while (rl[i] == ' ')
		{
			i++;
			if (rl[i] == '|')
				return (-1);
		}
	}
	return (0);
}

int	check_error_two(char *rl)
{
	int	i;
	
	i = 0;
	if ((rl[i] == '>' || rl[i] == '<') && !rl[i + 1])
		return (-1);
	if (rl[i] == '|' || rl[i] == ':' || rl[i] == '!')
		return (-1);
	while (rl[i])
		i++;
	if (rl[i - 1] == '>' || rl[i - 1] == '<' || rl[i - 1] == '|')
		return (-1);
	return (0);
}

int	check_error(char *rl)
{
	int	i;

	i = 0;
	if (rl != NULL && *rl == '\0')
		return (0);
	if (check_quote_close(rl) == -1)
		return (-1);
	if (check_error_two(rl) == -1)
		return (-1);
	while (rl[i])
	{
		if (rl[i] == 34 || rl[i] == 39)
		{
			i++;
			while (rl[i] != 34 && rl[i] && rl[i] != 39)
				i++;
		}
		if (check_rl(rl, i) == -1)
			return (-1);
		i++;
	}
	return (0);
}
