/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:10:09 by abolea            #+#    #+#             */
/*   Updated: 2024/04/18 17:57:22 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_error(char *rl)
{
	int	i;

	i = 0;
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
		i++;
	}
	return (0);
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
	fill_delim_tab(da, temp_args);
	fill_append_tab(da, temp_args);
	while (i < da->pnum)
	{
		if_quotes_not_close(temp_args, i);
		after_dollar(temp_args[i]);
		temp_args = new_temp_args(da, temp_args);
		words = ft_split(temp_args[i], ' ');
		while (words[num_words] != NULL)
		{
			num_words++;
		}
		da->args[i] = malloc((num_words + 1) * sizeof(char *));
		da->args[i][0] = fill_cmd(words);
		if (num_words > 1)
		{
			da->args[i][1] = fill_args(words);
			da->args[i][2] = NULL;
		}
		else
			da->args[i][1] = NULL;
		da->io_nb = 0;
		fill_intab(da, temp_args);
		fill_outab(da, temp_args);
		i++;
	}
	print_args(i, da->pnum, da);
}

int	main(int argc, char **argv, char **envp)
{
	char	*rl;
	t_data	da;

	(void)envp;
	if (argc != 1 || argv[0][0] == '\0')
		printf("ERROR\n");
	set_all(&da, envp);
	// print_all();
	while (1)
	{
		rl = readline("\033[1;36m<3 \033[0;37m");
		if (check_error(rl))
		{
			printf("parse error\n");
			continue ;
		}
		if (rl[0])
		{
			parsing(rl, &da);
			main_exec(&da, envp);
			add_history(rl);
			// free_struct(&da);
			free(rl);
		}
		else
			continue ;
	}
	return (0);
}
