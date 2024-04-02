/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:10:09 by abolea            #+#    #+#             */
/*   Updated: 2024/04/02 13:20:51 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_error(char *rl)
{
	int	i;

	i = 0;
	while (rl[i])
	{
		if (rl[i] == '<' && rl[i + 1] == '>')
			return (-1);
		else if (rl[i] == '>' && rl[i + 1] == '<')
			return (-1);
		else if (rl[i] == '>' && rl[i + 2] == '>')
			return (-1);
		else if (rl[i] == '<' && rl[i + 2] == '<')
			return (-1);
		i++;
	}
	return (0);
}

int	simple_quote_close(char *temp_args)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (temp_args[i])
	{
		if (temp_args[i] == 39)
		{
			i++;
			k++;
			while (temp_args[i])
			{
				if (temp_args[i] == 39)
					j++;
				i++;
			}
		}
		i++;
	}
	if (j == 0 && k != 0)
		return (0);
	return (1);
}

int	double_quotes_close(char *temp_args)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (temp_args[i])
	{
		if (temp_args[i] == 34)
		{
			i++;
			k++;
			while (temp_args[i])
			{
				if (temp_args[i] == 34)
					j++;
				i++;
			}
		}
		i++;
	}
	if (j == 0 && k != 0)
		return (0);
	return (1);
}


void	print_args(int i, int pnum, char ***args)
{
	int	j;

	i = 0;
	while (i < pnum)
	{
		printf("\nCommande %d:\n\n", i + 1);
		j = 0;
		while (j < 4)
		{
			printf("args[%d][%d] = %s\n", i, j, args[i][j]);
			j++;
		}
		i++;
	}
}

int	nb_pipe(char *rl)
{
	int	pnum;
	int	i;

	i = 0;
	pnum = 1;
	while (rl[i])
	{
		if (rl[i] == '|')
			pnum++;
		i++;
	}
	return (pnum);
}

int	ft_strlen_char(char *s, char c)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (s[i] == ' ')
		i++;
	while (s[len + i])
	{
		if (s[len + i] == c)
			break ;
		else
			len++;
	}
	return (len);
}

char	*cpy_until_char(char *s, char c)
{
	int		len;
	int		i;
	char	*tmp;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen_char(s, c);
	tmp = malloc((len + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	while (s[i] == ' ')
		i++;
	while (i < len + 1)
	{
		tmp[j] = s[i];
		i++;
		j++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*fill_input(char ** words, char **temp_args, int i)
{
	int		j;
	int		k;
	int		l;
	char	*tmp;
	char	*args;

	j = 1;
	tmp = ft_strdup("");
	if (ft_strnstr(temp_args[i], "<", ft_strlen(temp_args[i])))
	{
		args = ft_strdup("");
		while (words[j])
		{
			if (words[j - 1][0] == '<' && !words[j - 1][1])
			{
				args = ft_strjoin_ori(args, words[j]);
				args = ft_strjoin_ori(args, " ");
			}
			else if (words[j][0] == '<' && words[j][1])
			{
				k = 1;
				l = 0;
				while (words[j][k])
				{
					tmp[l] = words[j][k];
					l++;
					k++;
				}
				tmp[l] = '\0';
				args = ft_strjoin_ori(args, tmp);
				args = ft_strjoin_ori(args, " ");
			}
			j++;
		}
	}
	else
		args = NULL;
	return (args);
}


char	*fill_output(char ** words, char **temp_args, int i)
{
	int		j;
	int		k;
	int		l;
	char	*tmp;
	char	*args;

	j = 1;
	tmp = ft_strdup("");
	if (ft_strnstr(temp_args[i], ">", ft_strlen(temp_args[i])))
	{
		args = ft_strdup("");
		while (words[j])
		{
			if (words[j - 1][0] == '>' && !words[j - 1][1])
			{
				args = ft_strjoin_ori(args, words[j]);
				args = ft_strjoin_ori(args, " ");
			}
			else if (words[j][0] == '>' && words[j][1])
			{
				k = 1;
				l = 0;
				while (words[j][k])
				{
					tmp[l] = words[j][k];
					l++;
					k++;
				}
				tmp[l] = '\0';
				args = ft_strjoin_ori(args, tmp);
				args = ft_strjoin_ori(args, " ");
			}
			j++;
		}
	}
	else
		args = NULL;
	return (args);
}

void	if_quotes(char **temp_args, int i)
{
	if (simple_quote_close(temp_args[i]) == 0)
		exit(printf("Error : simple quote not close\n"));
	else if (double_quotes_close(temp_args[i]) == 0)
		exit(printf("Error : double quotes not close\n"));
	else
		return ;
}

int	pos_cmd(char **words)
{
	int	j;

	j = 1;
	if ((words[0][0] != '<' && words[0][0] != '>'))
		return (0);
	while (words[j])
	{
		if ((words[j - 1][0] != '<' && words[j - 1][0] != '>') && \
		(words[j][0] != '>' && words[j][0] != '<'))
			return (j);
		j++;
	}
	return (-1);
}

int	pos_args(char **words)
{
	int	j;

	j = pos_cmd(words) + 1;
	if (j == 0)
		return (-1);
	while (words[j])
	{
		if ((words[j - 1][0] !=  '<' && words[j - 1][0] != '>') && \
		(words[j][0] != '>' && words[j][0] != '<'))
			return (j);
		else if (((words[j - 1][0] == '<' && words[j - 1][0] == '>') || words[j - 1][1]) && \
		(words[j][0] != '>' && words[j][0] != '<'))
			return (j);
		j++;
	}
	return (-1);
}

char	*fill_cmd(char **words)
{
	char	*args;
	int		i;

	i = pos_cmd(words);
	if (i == -1)
		args = NULL;
	else
		args = ft_strdup(words[i]);
	return (args);
}

char	*fill_args(char **words)
{
	char	*args;
	int		j;
	int		num_words;

	num_words = 0;
	while (words[num_words])
		num_words++;
	j = pos_args(words);
	if (j == -1)
		args = NULL;
	else
	{
		args = ft_strdup("");
		while (j < num_words && words[j][0] != '<' && words[j][0] != '>')
		{
			args = ft_strjoin_ori(args, words[j]);
			args = ft_strjoin_ori(args, " ");
			j++;
		}
		while (j < num_words)
		{
			if ((words[j - 2][0] == '<' || words[j - 2][0] == '>') && !words[j - 2][1])
			{
				while (j < num_words && (words[j][0] != '<' && words[j][0] != '>'))
				{
					args = ft_strjoin_ori(args, words[j]);
					args = ft_strjoin_ori(args, " ");
					j++;
				}
			}
			else if ((words[j - 1][0] == '<' || words[j - 1][0] == '>') && words[j - 1][1])
			{
				while (j < num_words && (words[j][0] != '<' && words[j][0] != '>'))
				{
					args = ft_strjoin_ori(args, words[j]);
					args = ft_strjoin_ori(args, " ");
					j++;
				}
			}
			j++;
		}
	}
	return (args);
}

void	parsing(char *rl, t_data *da)
{
	char	**temp_args;
	char	**words;
	int		i;
	int		num_words;	

	i = 0;
	da->pnum = nb_pipe(rl);
	num_words = 0;
	temp_args = ft_split(rl, '|');
	da->args = malloc(da->pnum * sizeof(char **));
	while (i < da->pnum)
	{
		if_quotes(temp_args, i);
		words = ft_split(temp_args[i], ' ');
		while (words[num_words] != NULL)
			num_words++;
		da->args[i] = malloc((num_words + 1) * sizeof(char *));
		da->args[i][0] = fill_cmd(words);
		if (num_words > 1)
		{
			da->args[i][1] = fill_args(words);
			da->args[i][2] = fill_input(words, temp_args, i);
			da->args[i][3] = fill_output(words, temp_args, i);
		}
		else
		{
			da->args[i][1] = NULL;
			da->args[i][2] = NULL;
			da->args[i][3] = NULL;
		}
		i++;
	}
	print_args(i, da->pnum, da->args);
}


int	main(int argc, char **argv, char **envp)
{
	char	*rl;
	t_data	da;
	
	(void)envp;
	if (argc != 1 || argv[0][0] == '\0')
		printf("ERROR\n");
	while (1)
	{
		rl = readline("\033[1;36m<3 \033[0;37m");
		if (check_error(rl))
		{
			printf("parse error\n");
			continue;
		}
		if (rl[0])
		{
			parsing(rl, &da);
			// main_exec(&da, envp);
			add_history(rl);
		}
		else
			continue ;
	}
	return (0);
}
