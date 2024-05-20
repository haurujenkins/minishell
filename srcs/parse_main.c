/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:10:09 by abolea            #+#    #+#             */
/*   Updated: 2024/05/17 15:05:26 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_error(char *rl)
{
	int	i;

	i = 0;
	if (rl[i] == '|' || rl[i] == ';')
		return (-1);
	while (rl[i])
	{
		if (rl[i] == 34)
		{
			i++;
			while (rl[i] != 34 && rl[i])
				i++;
		}
		if (rl[i] == '<' && rl[i + 1] == '>')
			return (-1);
		else if (rl[i] == '>' && rl[i + 1] == '<')
			return (-1);
		else if (rl[i] == '<' && rl[i + 1] == '<' && rl[i + 2] == '<')
			return (-1);
		else if (rl[i] == '>' && rl[i + 1] == '>' && rl[i + 2] == '>')
			return (-1);
		else if (rl[i] == '>' && rl[i + 2] == '>')
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
		i++;
	}
	if (rl[i - 1] == '|' || rl[i - 1] == '>' || rl[i - 1] == '<')
		return (-1);
	return (0);
}

void	free_words_and_temp_args(char **temp_args, char **words)
{
	int	i;
	int	num_w;
	
	i = -1;
	while (temp_args[++i] != NULL)
		free(temp_args[i]);
	free(temp_args);
	num_w = -1;
	while (words[++num_w] != NULL)
		free(words[num_w]);
	free(words);
	words = NULL;
}


int	fill_all_tab(t_data *da, char **words, char **temp_args, int i)
{
	int	num_w;

	num_w = 0;
	while (words[num_w] != NULL)
		num_w++;
	da->args[i] = malloc((num_w + 1) * sizeof(char *));
	if (da->args[i] == NULL)
		return (1);
	da->args[i][0] = fill_cmd(words);
	da->args[i][1] = NULL;
	da->pos_cmd = pos_cmd(words);
	da->io_nb = 0;
	fill_args_tab(da, words, i);
	fill_intab(da, temp_args[i], i);
	fill_outab(da, temp_args[i], i);
	return (0);
}

int	parsing(char *rl, t_data *da)
{
	char	**temp_args;
	char	**words;
	int		i;	

	i = 0;
	temp_args = NULL;
	words = NULL;
	temp_args = init_temp_args(rl, da);
	if (temp_args == NULL)
		return (printf ("Error: malloc failed\n"), 1);
	if (init_malloc(temp_args, da) == 1)
		return (1);
	while (i < da->pnum)
	{
		words = init_words(temp_args, i);
		if (fill_all_tab(da, words, temp_args, i) == 1)
			return (printf("Error: malloc failed\n"), 1);
		i++;
	}
	free_words_and_temp_args(temp_args, words);
	print_args(i, da->pnum, da);
	return (0);
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
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		rl = readline("\033[1;36m<3 \033[0;37m");
		if (!rl)
		{
			//free_struct(&da);
			break ;
		}
		if (check_error(rl))
		{
			add_history(rl);
			write(2, "parse error\n", 12);
			continue ;
		}
		if (rl[0])
		{
			if (parsing(rl, &da) == 1)
			{
				add_history(rl);
				free(rl);
				free_struct(&da);
			}
			else
			{
				if (!(heredoc_replace(&da, 0) == -1))
				{
					signal(SIGINT, sigint_handler);
					print_args(0, da.pnum, &da);
					add_history(rl);
					free(rl);
					if (da.args[0][0])
						main_exec(&da, envp);
					free_struct(&da);
				}
			}
		}
	}
	return (0);
}
