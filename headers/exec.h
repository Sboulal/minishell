/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:48:35 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/09/21 18:56:55 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# define READ_END 0
# define WRITE_END 1
# include <stdio.h>
#include "lexer.h"
# include "../libft/libft.h"
# include <unistd.h>
# include "readline/readline.h"
# include "readline/history.h"
# include <signal.h>
# include <string.h>
# include <limits.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <errno.h>



t_export	*ft_lst_exp(t_export *exp);
t_export	*list_exp(char *env);
t_envp		*list_env(char *env);
t_envp		*ft_lst(t_envp *lst);
void		add_back_env(t_envp **lst, t_envp *new);
void		creat_env(t_envp **lst);
void		print_env(t_exec *exp);
int			check_arg(char **args, int k, int nbr, int len);
void		print_echo(char **arg, int nbr, t_exec *exp);
void	cd_derc(char **args, t_envp **list_env, t_exec **exp, t_mini *cmd);
void		exit_program(t_mini *cmd);
void		unset_env(t_exec **exp, char **arg);
char		**list_clean(char *cmd, int num);
void		add_to_export(t_exec **exec);
// int			ft_strcmp(const char *s1, const char *s2);
void		export(t_exec **exec);
void		sort_list(t_export **exp);
void		creat_exp(t_export **exp, t_envp *env);
void		add_back_exp(t_export **lst, t_export *new);
void		exec_cmd(t_exec **exp, char **env);
// void		buil_exec(t_exec *exp, t_mini *cmd, char **env);
void	exec_pipe(t_exec **exp, t_mini *cmd);
void	buil_exec_pipe(t_exec **exp, t_mini *cmd);
void		builtins(t_exec **exp, t_mini *cmd);
int		check_error_export(char *cmd, int i);
int			check_export(char *cmd);
void		use_pipe(t_exec **exp, t_mini *cmd);
int			sig(void);
void	print_in_echo(char **arg, int nbr_arg);
// void		parcing_cmd(char *cmd, char **env);
void		change_olde_pwd(t_envp **list, char *old);
int			sig_cmd(void);
void		edit_shlvl(t_exec **exp);
void		close_pipe(int **pip, int j);
void		edit_in_string(t_envp *env);
void		sort_utile(t_export *head, t_export *tomp);
void		close_file(int **pipfd, int nb_pip);
int			**incial_pipe(int nb_pip, t_exec *exp);
void		wait_pid(pid_t *pid, t_exec *exp);
char		*get_env(t_envp *list_env);
void		print_error_nor(char *str);
void		print_error_norr(char *str, int i);
void	protect_cmd(t_envp **env);
void	add_back_envstring(t_envp *env);
int	check_unset(char *cmd);
int	check_unset_env(char *cmd);
void	ft_delete(t_envp **head);
void	ft_delete_export(t_export **head);
void check_permision(t_mini *cmd);

#endif