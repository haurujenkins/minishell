/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:10:09 by abolea            #+#    #+#             */
/*   Updated: 2024/03/21 10:59:02 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../includes/minishell.h"


void	print_args(int	i, int pnum, char ***args)
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

char	*cpy_until_char(char *s, char c)
{
	int		len;
	int		i;
	char	*tmp;
	
	i = 0;
	len = 0;
	while (s[len])
	{
		if (s[len] == c)
			break;
		else
			len++;
	}
	tmp = malloc(len * sizeof(char));
	while (i < len)
	{
		tmp[i] = s[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*fill_input(char **temp_args, char **words, int i)
{
	char	*args;
	char	*tmp;
	int		num_words;
	int		j;

	if (ft_strnstr(temp_args[i], "<", ft_strlen(temp_args[i])))
		{
			num_words = 0;
			args = ft_strdup("");
			tmp = args;
			words = ft_split_file(temp_args[i], '<');
			while (words[num_words] != NULL)
				num_words++;
			if (num_words > 1)
			{
				j = 1;
				while (j < num_words)
				{
					tmp = cpy_until_char(words[j], '>');
					args = ft_strjoin(args, tmp);
					j++;
				}
			}
		}
	else
		args = NULL;
	return (args);
}

char	*fill_output(char **temp_args, char **words, int i)
{
	char	*args;
	char	*tmp;
	int		num_words;
	int		j;

	if (ft_strnstr(temp_args[i], ">", ft_strlen(temp_args[i])))
		{
			num_words = 0;
			args = ft_strdup("");
			tmp = args;
			words = ft_split_file(temp_args[i], '>');
			while (words[num_words] != NULL)
				num_words++;
			if (num_words > 1)
			{
				j = 1;
				while (j < num_words)
				{
					tmp = cpy_until_char(words[j], '<');
					args = ft_strjoin(args, tmp);
					j++;
				}
			}
		}
	else
		args = NULL;
	return (args);
}

char *fill_args(char **words)
{
	char	*args;
	int		num_words;
	int		j;

	num_words = 0;
	while (words[num_words] != NULL)
			num_words++;	
	j = 1;
	args = ft_strdup("");
	if (num_words > 1)
	{
		while (j < num_words)
		{
			if (ft_strnstr(words[j], "<", 1) || ft_strnstr(words[j], ">", 1))
				return (args);
			args = ft_strjoin(args, words[j]);
			j++;
			if (j < num_words)
				args = ft_strjoin(args, " ");
		}
	}
	else
		args = NULL;
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
		words = ft_split(temp_args[i], ' ');
		while (words[num_words] != NULL)
			num_words++;
		da->args[i] = malloc((num_words + 1) * sizeof(char *));
		da->args[i][0] = ft_strdup(words[0]);
		num_words = 0;
		da->args[i][1] = fill_args(words);
		da->args[i][2] = NULL;
		da->args[i][3] = NULL;
		da->args[i][2] = fill_input(temp_args, words, i);
		da->args[i][3] = fill_output(temp_args, words, i);
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
		if (rl[0])
		{
			parsing(rl, &da);
			// main_exec(args, envp, pnum);
			add_history(rl);
			free(rl);
		}
		else
			continue;
	}
	return (0);
}
