/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 13:59:33 by abolea            #+#    #+#             */
/*   Updated: 2024/05/21 11:48:56 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_args(int i, int pnum, t_data *da)
{
	int	d;
	int	j;
	int	k;
	int	l;
	int	m;
	int	n;

	i = 0;
	while (i < pnum)
	{
		printf("\033[1;34m\nCommande %d:\033[0;37m\n\n", i + 1);
		j = 0;
		printf("\033[0;31mcmd[%d][%d]\033[0;37m = %s\n", i, j, da->args[i][0]);
		j++;
		d = 0;
		if (da->args_tab[i][d])
			printf("\n");
		while (da->args_tab[i][d])
		{
			printf("\033[0;33margs[%d][%d]\033[0;37m = %s\n", i, d, da->args_tab[i][d]);
			d++;
		}
		k = 0;
		if (da->in_tab[i][k])
			printf("\n");
		while (da->in_tab[i][k])
		{
			printf("\033[0;32minput[%d][%d]\033[0;37m = %s\n", i, k, da->in_tab[i][k]);
			k++;
		}
		l = 0;
		if (da->out_tab[i][l])
			printf("\n");
		while (da->out_tab[i][l])
		{
			printf("\033[0;35moutput[%d][%d]\033[0;37m = %s\n", i, l, da->out_tab[i][l]);
			l++;
		}
		m = 0;
		if (da->delim_tab[i][m])
			printf("\n");
		while (da->delim_tab[i][m])
		{
			printf("delimiteur[%d][%d]\033[0;37m = %s\n", i, m, da->delim_tab[i][m]);
			m++;
		}
		n = 0;
		if (da->append_tab[i][n])
			printf("\n");
		while (da->append_tab[i][n])
		{
			printf("append_out[%d][%d]\033[0;37m = %s\n", i, n, da->append_tab[i][n]);
			n++;
		}
		i++;
	}
	printf("\n");
}

void	loading(int p)
{	
	int i;

	i = 0;
	printf("[");
	while (i < 50)
	{
		if (i < p / 2)
			printf("=");
		else
            printf(" ");
		i++;
	}
	printf("] %d%%\r", p);
}

void	print_title()
{
    printf("\n ███    ███ ██ ███    ██ ██ ███████ ██   ██ ███████ ██      ██      \033[0m\n"); // Rouge
    printf(" ████  ████ ██ ████   ██ ██ ██      ██   ██ ██      ██      ██      \033[0m\n"); // Vert
    printf(" ██ ████ ██ ██ ██ ██  ██ ██ ███████ ███████ █████   ██      ██      \033[0m\n"); // Jaune
    printf(" ██  ██  ██ ██ ██  ██ ██ ██      ██ ██   ██ ██      ██      ██      \033[0m\n"); // Bleu
    printf(" ██      ██ ██ ██   ████ ██ ███████ ██   ██ ███████ ███████ ███████ \033[0m\n"); // Magenta
    printf("\033[0m");
	printf("                                                                    \n");
	
}

void	print_all()
{
	int		p;
	
	p = 0;
	while (p <= 100) 
	{
		loading(p);
		usleep(10000);
		p++;
	}
	printf("\n");
	print_title();
}
