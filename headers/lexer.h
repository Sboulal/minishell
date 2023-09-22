 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:25:08 by saboulal          #+#    #+#             */
/*   Updated: 2023/09/12 17:48:38 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include<stdbool.h>
#include"../libft/libft.h"
#include<fcntl.h>
#include<signal.h>
#define WORD -1
#define	PIPE_LINE  0
#define	REDIRECTION 1
#define HERE_DOC 3
#define OPERATOR 2
#define LIMITER 4

#define READ_END 0
#define WRITE_END 1
#define FILE 5

typedef struct s_envp
{
	char			*env;
	char			*variable;
	char			*value;
	struct s_envp	*next;
}	t_envp;

typedef struct s_glob
{
    char **env;
	t_envp *envp;
	int heredoc_flag;
    int status;
}t_glob;

t_glob g_var;
// typedef enum e_token
// {
// 	 //end command 
// }t_token;
typedef struct s_lexer
{
	char *token;
	int 	type;
	int pipe[2];
	struct s_lexer *next;
}t_lexer;

// typedef struct s_redir
// {
// 	t_token			tok;
// 	char			*file;
// 	bool			flg;
// 	int				fd;
// 	struct s_redir	*lchild;
// 	struct s_redir	*rchild;
// }t_redir;

typedef struct s_mini
{
   char *cmd; // command "ls"
    char **arg; // argument of command "-la"
    int nbr_arg; // number of command "2"
   	int	fd[2];
    struct s_mini *next;
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
	t_envp		*env;
	char 		**env_string;
	int			nbr_cmd;
}t_exec;

t_lexer *create_node(char *s);
void add_back(t_lexer **head, char *s);
void	add_middle(t_lexer *token, char *word);
char **skip_vid(char *str);
int count_string(char *str);
int is_isspace(char c);
int next_quote(int i, char quote,char *str);
char	*get_word(char *s, size_t *index);
int	check_token(char *s);
void	close_fds(t_mini *cmd);
char	**my_split(char *line, int wc);
char	*here_doc_name(void);
void	*tabfree(char **tab);
void	close_fds(t_mini *cmd);
void	handle_pipes(t_mini *cmd, t_lexer *tokens);
int	handle_redirection(t_mini *cmd, t_lexer *tokens, t_envp *env);
t_mini	*handle_cmd(t_mini *cmd, t_lexer *tokens);
t_mini *parse(char *str, t_envp *env);
int	position_of_operator(char *s);
int	is_operator(char c);
char	*heredoc_expansion(char *line, t_envp *env);
void	ft_close(int fd);
int check_parse(t_lexer *lexer);
int check_pipes(t_lexer *lexer);
int word_after(t_lexer *lexer);
int check_redirections(t_lexer *lexer);
int check_invalid_operator(t_lexer *lexer);
void 	token_herdoc(t_lexer *lexer);
int	redirect(t_mini *cmd, char *type, char *file, t_envp *env);
void	check_and_redirect(int *inf_out, int fd);
int	ft_open(char *path, int flags, int mode);
t_lexer *expand_lexer(t_lexer *our_lexer, t_envp *env);
char	*quotes_removal(char *token);
char	*trim_quotes(char *token, int quotes_len);
char *parameter_expansion(char *tok, t_envp *env);
t_lexer	*remove_empty_tokens(t_lexer *tokens, t_lexer *head, t_lexer *prev);
char *get_name(char *tok,t_envp *env);
int	get_name_len(char *token, int i);
char	*get_env_value(char *name, t_envp *env);
char	*get_name_here(char *token);
void	ft_dup2(int oldfd, int newfd);
char	*replace_name_value_here(char *token, char *name, char *value);
int	replace_before_name_here(char *new_token, char *token);
char	*replace_name_value(char *token, char *name, char *value);
void	free_all(t_lexer *tokens);
void	free_tokens(t_lexer *tokens);
t_lexer	*add_cmd(t_mini **cmds, t_lexer *tokens, t_envp *env);
t_mini	*convert_to_cmds(t_lexer *tokens, t_envp *env);
void	open_pipes(t_lexer	*tokens);
t_lexer	*next_pipe(t_lexer *tokens);
int is_identifier(char c);
int number_word_ident(char *token);
void	expands_dollars_dollars(char *token);
void	free_token_word(t_lexer *token, char *word);
void	check_and_redirect(int *inf_out, int fd);
void	expands_dollars_dollars(char *token);
int		ft_pipe(int fd[2]);
void	ft_exit(int status, char *msg);
int	is_env_name(char c);
int	handle_heredocs(t_mini *cmd, t_lexer *tokens, t_envp *env);
int	is_expand(char **limiter);
void	change_flag(int s);
void	sigint_heredoc(void);
int	handle_heredoc_suite(t_mini *cmd, char *limiter, char *file, int fd);
void	check_heredoc(void);
int	handle_heredoc(t_mini *cmd, char *limiter, char *file, t_envp *env);
int	word_split_count(char *line);
t_lexer	*word_spliting(t_lexer *token);
#endif