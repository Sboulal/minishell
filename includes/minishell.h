/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 01:41:47 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/10/07 11:29:38 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include <fcntl.h>
# include <signal.h>
# include <string.h>
# define WORD -1
# define PIPE_LINE  0
# define REDIRECTION 1
# define HERE_DOC 3
# define OPERATOR 2
# define LIMITER 4
# define READ_END 0
# define WRITE_END 1
# define FILE 5

typedef struct s_gn
{
	int		i;
	char	*str;
}	t_gn;

typedef struct s_envp
{
	char			*env;
	char			*variable;
	char			*value;
	struct s_envp	*next;
}	t_envp;
typedef struct s_glob
{
	int	sig_heredoc;
	int	sig_status;
}t_glob;

t_glob	g_var;

typedef struct s_lexer
{
	char			*token;
	int				type;
	int				y;
	char			*str;
	int				am;
	int				pipe[2];
	struct s_lexer	*next;
}t_lexer;

typedef struct s_mini
{
	char			**arg;
	char			*cmd;
	int				x;
	int				nbr_arg;
	int				fd[2];
	struct s_mini	*next;
}t_mini;

typedef struct s_export
{
	char			*exp;
	char			*variable;
	char			*value;
	struct s_export	*next;
}	t_export;

typedef struct s_exec
{
	t_export	*exp;
	t_mini		*cmd;
	int			nbr_cmd;
	char		**env_string;
	t_envp		*env;
}	t_exec;

t_lexer	*create_node(char *s);
t_mini	*handle_cmd(t_mini *cmd, t_lexer *tokens);
t_mini	*parse(char *str, t_envp *env);
t_lexer	*remove_empty_tokens(t_lexer *tokens, t_lexer *head, t_lexer *prev);
t_lexer	*add_cmd(t_mini **cmds, t_lexer *tokens, t_envp *env);
t_mini	*convert_to_cmds(t_lexer *tokens, t_envp *env);
t_lexer	*next_pipe(t_lexer *tokens);
t_lexer	*word_spliting(t_lexer *token);
void	add_back(t_lexer **head, char *s);
void	add_middle(t_lexer *token, char *word);
char	**skip_vid(char *str);
void	close_all_fds(t_mini *head);
void	free_cmd(t_mini *head);
int		count_string(char *str);
int		next_quote(int i, char quote, char *str);
char	*get_word(char *s, size_t *index);
int		check_token(char *s);
char	**my_split(char *line, int wc);
char	*here_doc_name(void);
void	*tabfree(char **tab);
void	handle_pipes(t_mini *cmd, t_lexer *tokens);
int		handle_redirection(t_mini *cmd, t_lexer *tokens, t_envp *env);
int		position_of_operator(char *s);
int		is_operator(char c);
char	*heredoc_expansion(char *line, t_envp *env);
void	ft_close(int fd);
int		check_parse(t_lexer *lexer);
int		check_pipes(t_lexer *lexer);
int		word_after(t_lexer *lexer);
int		check_redirections(t_lexer *lexer);
int		check_invalid_operator(t_lexer *lexer);
void	token_herdoc(t_lexer *lexer);
int		redirect(t_mini *cmd, char *type, char *file, t_envp *env);
void	check_and_redirect(int *inf_out, int fd);
int		ft_open(char *path, int flags, int mode);
t_lexer	*expand_lexer(t_lexer *our_lexer, t_envp *env);
char	*quotes_removal(char *token);
char	*trim_quotes(char *token, int quotes_len);
char	*get_name(char *tok, t_envp *env, t_lexer *tokens);
int		get_name_len(char *token, int i);
char	*get_env_value(char *name, t_envp *env);
char	*get_name_here(char *token);
void	ft_dup2(int oldfd, int newfd);
char	*replace_name_value_here(char *token, char *name, char *value);
int		replace_before_name_here(char *new_token, char *token);
void	free_all(t_lexer *tokens);
void	free_tokens(t_lexer *tokens);
int		is_identifier(char c);
void	expands_dollars_dollars(char *token);
void	free_token_word(t_lexer *token, char *word);
void	check_and_redirect(int *inf_out, int fd);
void	expands_dollars_dollars(char *token);
int		ft_pipe(int *fd);
int		is_env_name(char c);
int		handle_heredocs(t_mini *cmd, t_lexer *tokens, t_envp *env);
int		is_expand(char **limiter);
void	change_flag(int s);
void	sigint_heredoc(void);
int		handle_heredoc_suite(t_mini *cmd, char *limiter, char *file, int fd);
void	check_heredoc(void);
int		handle_heredoc(t_mini *cmd, char *limiter, char *file, t_envp *env);
int		word_split_count(char *line);
void	remove_quote_d(char **str, int *i, char **src);
void	remove_quote_s(char **str, int *i, char **src);
char	*to_string(char c);
char	*get_name_quot(char *token, t_envp *env);
int		expand_exit(char *token, int *i, char **str);
int		expand_exit_null(char *token, int *i, char **str);
int		expand_do(char *token, int *i, char **str, t_envp *env);
int		expand_doubl(char *token, int *i, char **str, t_envp *env);
int		expand_do_nor(char *token, int **i, char **str);
t_list	*cmd_list(t_lexer *tokens);
void	cmd_repl_nor(t_mini **cmd, t_list	**list);
t_list	*cmd_repl(t_lexer *tokens, t_mini **cmd, int *i);
t_mini	*arg_repl(t_list *list, int i, t_mini **cmd);
void	ft_lstclear(t_list **lst);
int		cmt_string(char **env);
char	**creat_string_env(char **env);
int		check_line(int ac, char **av);
int		check_env(t_exec *exec, char **env, int	*k);
int		exec_part(t_exec *exec, char **env);
void	check_fd(t_mini *head, t_exec *exec, char *bas);
int		ft_read(char *line);
void	clear_end(t_exec	*exec);
int		is_isspace(char c);
void	ft_lstclear_cmd(t_mini **lst);
void	ft_lstclear_exp(t_export **lst);
void	ft_lstclear_env(t_envp **lst);
void	ft_add_history(char *bas);
void	remove_empty_norm(t_lexer **tokens, t_lexer **prev, t_lexer **head);
void	remove_empty_first(t_lexer **tokens, t_lexer **head);
void	free_node(t_lexer *tokens);
void	remove_empty_last(t_lexer **tokens, t_lexer **prev);
int		expand_singl(char *token, int *i, char **str);
int		expand_doubl(char *token, int *i, char **str, t_envp *env);
int		expand_dolar(char *token, int *i, char **str, t_envp *env);
void	add_ambg(t_lexer **lexer);
#endif