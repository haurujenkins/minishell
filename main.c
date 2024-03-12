/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolea <abolea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:31:58 by abolea            #+#    #+#             */
/*   Updated: 2024/03/12 15:45:36 by abolea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(int argc, char **argv, char **emvp)
{
	char	*rl;

	if (argc != 1)
		printf("ERROR\n");
	while (1)
	{
		rl = readline("~ ");
		add_history(rl);
	}
	return (0);
}