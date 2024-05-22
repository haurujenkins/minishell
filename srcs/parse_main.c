/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:10:09 by abolea            #+#    #+#             */
/*   Updated: 2024/05/22 14:18:45 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_rl(char *rl, int i)
{
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
	return (0);
}

int	check_error(char *rl)
{
	int	i;

	i = 0;
	if (rl[i] == '|' || rl[i] == ';')
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
	//print_args(i, da->pnum, da);
	return (0);
}

void	sigint_handler_main(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	stop_execution = 1;
} 

int	main(int argc, char **argv, char **envp)
{
	char			*rl;
	t_data			da;

	(void)envp;
	if (argc != 1 || argv[0][0] == '\0')
		printf("ERROR\n");
	set_all(&da, envp);
	while (1)
	{
		signal(SIGINT, sigint_handler_main);
		signal(SIGQUIT, SIG_IGN);
		rl = readline("\033[1;36m<3 \033[0;37m");
		if (stop_execution == 1)
		{
			stop_execution = 0;
			da.exit_status = 130;
		}
		if (!rl)
		{
			write(1, "exit\n", 5);
			//free_struct(&da);
			break ;
		}		
		if (check_error(rl))
		{
			da.exit_status = 2;
			write(2, "parse error\n", 12);
			continue ;
		}
		if (rl[0])
		{
			add_history(rl);
			if (parsing(rl, &da) == 1)
				free_struct(&da);
			else
			{
				if (!(heredoc_replace(&da, 0) == -1))
				{
					signal(SIGINT, sigint_handler);
					print_args(0, da.pnum, &da);
					if (da.args[0][0])
						main_exec(&da, envp);
					// free_struct(&da);
				}
			}
			free(rl);
			del_tmpfiles(&da, 0);
		}
	}
	return (0);
}
