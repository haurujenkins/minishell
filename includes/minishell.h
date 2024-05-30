/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-pier <lle-pier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:48:53 by lle-pier          #+#    #+#             */
/*   Updated: 2024/05/30 16:59:14 by lle-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <sys/stat.h>
# include "../libft/libft.h"
# include <termios.h>
# include <errno.h>
# include <limits.h>
# define MAX_INPUT_LENGTH 1024
# define TMPFILE_NAME ".heredoc/minishell_heredoc_tmpfile"
# define MAX_RANDOM_BYTES 8

extern	volatile sig_atomic_t	g_stop_execution;

typedef struct s_signals
{
	char	*endof;
	int		nb_delim;
	int		exit;
	int		heredoc;
}			t_signals;

typedef struct data_s
{
	int			i;
	int			j;
	int			line;
	int			out;
	char		**my_env;
	char		**cmd1;
	char		**my_path;
	char		*cmd;
	char		*point_path;
	int			fd_input;
	int			fd_output;
	int			fail_pipe;
	bool		freed;
	int			**pipefd;
	pid_t		pid1;
	pid_t		pid2;
	int			pnum;
	char		***args;
	char		***in_tab;
	char		***out_tab;
	int			p_in;
	int			p_out;
	int			check_export;
	int			exit_status;
	char		***delim_tab;
	char		***append_tab;
	int			nb_redir_in;
	int			nb_redir_out;
	int			io_nb;
	int			i_in_quotes;
	int			o_in_quotes;
	int			nb_delim;
	int			in_delim;
	int			o_append;
	int			nb_append;
	char		***args_tab;
	int			nb_args;
	int			i_args;
	int			pos_cmd;

	char		**words;
	pid_t		*children;
	t_signals	mysignal;
	int			nb_d;
	int			q_heredoc;
	int			if_heredoc;
}				t_data;

void	get_args(t_data *da, char **envp, int index);
void	set_pipe(t_data *da);
int		main_exec(t_data *da, char **envp);
int		check_files(t_data *da, int index);
void	exec_cmd(t_data *da, char **envp, int index);
void	check_cmd(t_data *da, int i, char **envp);
void	check_cmd_stat(t_data *da);
void	check_exec_exit(int index, t_data *da, int child_status);
void	set_all(t_data *da, char **envp, int i);
void	free_data(t_data *da, char **envp);
int		check_builtins(t_data *da, int index);
int		check_extern_builtins(t_data *da, char **envp, int index);
int		cd_case(t_data *da, int index, char **envp);
int		export_case(t_data *da, int index, char **envp);
int		exit_case(t_data *da, int index, char **envp);
void	exit_number(t_data *da, long long i, long long j);
int		unset_case(t_data *da, int index, int i, char **envp);
char	*get_home(char **envp);
void	close_fd(t_data *da, int index);
int		ft_tablen(char **tab);
char	**ft_realloc(char **tab, int size);
int		get_args_builtins(t_data *da, int index, char **envp);
int		my_cd(char **cmd, char **envp, t_data *da);
int		cd_error(char *path, t_data *da);
void	my_pwd(void);
int		my_echo(char **cmd, int i, int j, int flag);
void	echo_option(bool *newline, char **cmd, int i, int *flag);
void	my_env(char **env, int num);
void	my_export(t_data *da, int i, int k, int return_value);
void	print_export(char **env, int i, int j);
int		export_errors(t_data *da, int k);
int		char_error_export(t_data *da, int k, int i);
int		while_not_equal(t_data *da, int k, int i);
void	check_export_zero(t_data *da, int i, char *temp_cmd, char *temp_value);
void	export_pwd(t_data *da, char *temp_value);
int		my_unset(t_data *da, int k);
int		check_unset(t_data *da, int k);
void	sort_env(t_data *da);
void	free_pipe(t_data *da);
void	free_struct(t_data *da);
void	free_cmd_notfound(t_data *da);
void	export_pwd(t_data *da, char *temp_value);
void	infile_error(t_data *da, int index, int i);
char	*read_until_delimiter(char *delimiter, t_data *da);
void	outfile_error(t_data *da, int index, int i);
void	outfile_stat(t_data *da, int index, int i);
int		outfile_extern_error(t_data *da, int index, int i);
int		extern_outfile_stat(t_data *da, int index, int i);
void	check_infile(t_data *da, int index);
void	infile_stat(t_data *da, int index, int i);
void	check_outfile(t_data *da, int index);
void	exit_free(t_data *da);
void	free_tab(char **tab);
void	sigquit_handler_child(int signum);
void	sigint_handler_child(int signum);
void	sigint_handler_main(int signum);
void	sigint_handler(int signum);
void	sigquit_handler_doc(t_data *da);
void	set_flag(void);
int		heredoc_replace(t_data *da, int index, int i);
int		handler_while(t_data *da, char *line, char *delimiter, int fd);
int		handler_callback(t_data *da, int fd, char *line);
void	count_delim(t_data *da, int index);
void	del_tmpfiles(t_data *da, int index);
int		check_unset(t_data *da, int k);
void	free_cmd(t_data *da);
int		nb_quotes_in_quotes(char *s);
void	exit_child(t_data *da);

void	print_args(int i, int pnum, t_data *da);
void	loading(int p);
void	print_title();
void	print_all();
int		ft_nb_redir(char *temp_args, char c);
int		fill_append_tab(t_data *da, char **temp_args);
char	*sup_append(char *s);
int		len_without_append(char *s);
int		fill_delim_tab(t_data *da, char **temp_args);
char	*sup_delim(char *s);
char	*cpy_until_char(char *s, char c, int start);
int		if_finish_quotes(char *s);
int		if_finish_squotes(char *s);
int		fill_outab(t_data *da, char *temp_args, int i);
int		fill_intab(t_data *da, char *temp_args, int i);
void	if_quotes_not_close(char **temp_args, int i);
int		if_io_before_last_quotes(char *s, char c, int start);
int		if_quotes(char *s, int start);
char	*cpy_args_without_quotes(char *s);
char	*fill_args(t_data *da, char **words, int i);
char	*fill_cmd(char **words);
int		new_temp_args(t_data *da, char **temp_args);
int		nb_pipe(char *rl);
int		nb_io(char *s);
int		nb_quotes(char *s);
int		if_dollar(char *s);
int		len_env(t_data *da, char *s);
char	*find_in_env(t_data *da, char *s);
char	*after_dollar(char *s);
char	*temp_without_dollar(t_data *da, char *temp_args);
char	*get_cmd(char *words);
int		len_cmd(char *words);
int		double_quotes_close(char *temp_args);
char	*cpy_for_args(char *s, int start);
int		len_for_args(char *s, int start);
int		fill_args_tab(t_data *da, char **temp_args, int i);
int		pos_cmd(char **words);
char	*cpy_args_without_s_quotes(char *s);
char	*new_temp(char *s);
int		nb_dollars(char *s);
char	*all_positive(char *s);
char	*negative_in_quotes(char *s);
char	*dollar_negative_in_s_quote(char *s);
char	**init_words(char **temp_args, int i);
char	**init_temp_args(char *rl, t_data *da);
int		init_malloc(char **temp_args, t_data *da);
char	*new_temp_d(char *s);
char	*sup_d_quotes_before_dollar(char *s);
char	*sup_backslash_before_dollar(char *s);
void	set_parse(t_data *da);
char	*sup_tab(char *s);
int		len_without_append(char *s);
int		ft_nb_append(char *s);
int		len_without_delim(char *s);
int		ft_nb_delim(char *s);
char	*temp_without_dollar(t_data *da, char *temp_args);
char	*if_res_is_null(char *before_args, char *temp_args, char *new_args);
char	*cpy_in_res(char *res, char *temp_args, char *new_args);
void	copy_remaining(char *res, char *temp_args, int *i, int *j);
void	skip_chars_after_dollar(char *temp_args, int *i);
void	cpy_interrogation(char *res, char *temp_args, int *i, int *j);
void	copy_new_args(char *res, char *new_args, int *j);
void	copy_until_dollar(char *res, char *temp_args, int *i, int *j);
char	*return_new_args(char *new_args, char *before_args, t_data *da);
char	*if_not_new_args(char *before_args);
char	*recup_after_digit(char *s);
char	*recup_after_dollar(char *s, char *tmp);
char	*after_dollar(char *s);
char	*s_quotes_new_args_negative(char *s);
char	*add_d_quotes_newargs(char *s);
int		s_quotes_dollar(char *s);
char	*sup_s_quotes_before_dollar(char *s);
int		d_quotes_dollar(char *s);
char	*sup_d_quotes_before_dollar(char *s);
int		len_without_dollar_before_quotes(char *s);
char	*dollar_after_heredoc(char *s, t_data *da);
void	heredoc_double_quotes(char *s, t_data *da);
int		if_not_heredoc(t_data *da, char **temp_args, int i);
char	*cpy_in_res_without_dollar_quotes(char *res, char *s, int i, int j);
char	*sup_dollar_before_quotes(char *s);
char	*args_before(t_data *da, char **words, char *args);
char	*else_args_before_quotes(t_data *da, char **words, char *args, int i);
char	*else_args_before(t_data *da, char **words, char *args);
char	*if_args_before_ok(t_data *da, char **words, char *args, int i);
char	*if_args_after_ok(t_data *da, char **words, char *args);
int		if_args_after(char **words, int *j);
int		if_args_before(char **words, int *j);
int 	ft_nb_args(t_data *da, char **words);
char	*args_after(t_data *da, char **words, char *args);
char	*else_args_after(t_data *da, char **words, char *args);
char	*cpy_in_res_without_d_quotes(char *res, char *s);
char	*cpy_res_with_s_quotes(char *tmp, char *s, int i, int j);
char	*add_s_quote(char *s);
int		if_nb_dollar(char **temp_args, int i);
int		sup_append_and_delim(char **temp_args, int i);
int		check_quote_close(char	*rl);
int		check_rl_two(char *rl, int i);
int		check_rl(char *rl, int i);
int		check_error_two(char *rl);
int		check_error(char *rl);
void	free_words_and_temp_args(char **temp_args, char **words);
void	free_words(char **words);
void	free_temp_args(char **temp_args);
int		len_without_double_space(char *s);
char	*cpy_without_double_spaces(char *s, char *tmp, int i);
char	*sup_double_space(char *s);
char	*cpy_tmp_with_space(char *s, char *tmp, int in_quotes, int i);
char	*temp_with_space(char *s);
int		pos_args(t_data *da, char **words);
char	*cpy_after_digit(char *s, char *res);
int		len_after_digit(char *s);
int		nb_after_dollar(char *s);
int		len_after_dollar(char *s);
int		nb_dollars(char *s);

#endif