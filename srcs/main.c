/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:10:09 by abolea            #+#    #+#             */
/*   Updated: 2024/04/03 12:56:50 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	simple_quote_close(char *temp_args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (temp_args[i])
	{
		if (temp_args[i] == 39)
		{
			i++;
			while (temp_args[i])
			{
				if (temp_args[i] == 39)
					j++;
				i++;
			}
		}
		i++;
	}
	if (j == 0)
		return (0);
	return (1);
}

int	double_quotes_close(char *temp_args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (temp_args[i])
	{
		if (temp_args[i] == 34)
		{
			i++;
			while (temp_args[i])
			{
				if (temp_args[i] == 34)
					j++;
				i++;
			}
		}
		i++;
	}
	if (j == 0)
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
		words = ft_split(temp_args[i], '<');
		while (words[num_words] != NULL)
			num_words++;
		if (num_words > 1)
		{
			j = 1;
			while (j < num_words)
			{
				tmp = cpy_until_char(words[j], ' ');
				args = ft_strjoin_ori(args, tmp);
				args = ft_strjoin_ori(args, " ");
				j++;
			}
		}
	}
	else
		args = NULL;
	return (args);
}

char	*replace_char(char *s, char c1, char c2)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c1)
			s[i] = c2;
		i++;
	}
	return (s);
}

char	*fill_input_begin(char **temp_args, char **words, int i)
{
	char	*args;
	char	*tmp;
	int		num_words;
	int		j;

	num_words = 0;
	args = ft_strdup("");
	tmp = args;
	words = ft_split(temp_args[i], ' ');
	while (words[num_words] != NULL)
		num_words++;
	if (num_words > 1)
	{
		j = 1;
		while (j < num_words - 1)
		{
			tmp = cpy_until_char(words[j], ' ');
			args = ft_strjoin_ori(args, tmp);
			j++;
		}
	}
	else
		args = NULL;
	replace_char(args, '<', ' ');
	j = 0;
	while (args[j])
		j++;
	if (j == 0)
		return (NULL);
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
		words = ft_split(temp_args[i], '>');
		while (words[num_words] != NULL)
			num_words++;
		if (num_words > 1)
		{
			j = 1;
			while (j < num_words)
			{
				tmp = cpy_until_char(words[j], ' ');
				args = ft_strjoin_ori(args, tmp);
				args = ft_strjoin_ori(args, " ");
				j++;
			}
		}
	}
	else
		args = NULL;
	return (args);
}

char	*fill_args(char **words)
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
			args = ft_strjoin_ori(args, words[j]);
			args = ft_strjoin_ori(args, " ");
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
		//if_quotes(temp_args, i);
		words = ft_split(temp_args[i], ' ');
		while (words[num_words] != NULL)
			num_words++;
		da->args[i] = malloc((num_words + 1) * sizeof(char *));
		if (words[0][0] == '<' || words[0][0] == '>')
		{
			if (words[num_words - 2][0] != '<' && \
			words[num_words - 2][0] != '>')
				da->args[i][0] = ft_strdup(words[num_words - 1]);
			else
				da->args[i][0] = NULL;
			da->args[i][1] = NULL;
			da->args[i][2] = fill_input_begin(temp_args, words, i);
			if (da->args[i][2] == NULL)
				exit(printf("zsh: no such file or directory: %s\n", words[1]));
			da->args[i][3] = NULL;
		}
		else
			da->args[i][0] = ft_strdup(words[0]);
		if (num_words > 1 && (words[0][0] != '<' && words[0][0] != '>'))
		{
			da->args[i][1] = fill_args(words);
			if (da->args[i][1][0] == '\0')
				da->args[i][1] = NULL;
			da->args[i][2] = NULL;
			da->args[i][3] = NULL;
			da->args[i][2] = fill_input(temp_args, words, i);
			da->args[i][3] = fill_output(temp_args, words, i);
		}
		else if (words[0][0] != '<' && words[0][0] != '>')
		{
			da->args[i][1] = NULL;
			da->args[i][2] = NULL;
			da->args[i][3] = NULL;
		}
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*rl;
	t_data	da;

	(void)envp;
	if (argc != 1 || argv[0][0] == '\0')
		printf("ERROR\n");
	set_all(&da, envp);
	while (1)
	{
		rl = readline("\033[1;36m<3 \033[0;37m");
		if (rl[0])
		{
			parsing(rl, &da);
			main_exec(&da, envp);
			add_history(rl);
		}
		else
			continue ;
	}
	return (0);
}
