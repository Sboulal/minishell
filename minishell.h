/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:25:08 by saboulal          #+#    #+#             */
/*   Updated: 2023/07/08 14:10:04 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
// typedef enum e_token
// {
// 	WORD = -1,
// 	WHITE_SPACE = ' ',
// 	NEW_LINE = '\n',
// 	QOUTE = '\'',
// 	DOUBLE_QOUTE = '\"',
// 	ESCAPE = '\\',
// 	ENV = '$',
// 	PIPE_LINE = '|',
// 	REDIR_IN = '<',
// 	REDIR_OUT = '>',
// 	AND = '&',
// 	HERE_DOC,
// 	DREDIR_OUT,
// }t_token;

typedef struct token
{
	char *value;
	enum
	{
		WORD = -1,
		WHITE_SPACE = ' ',
		NEW_LINE = '\n',
		QOUTE = '\'',
		DOUBLE_QOUTE = '\"',
		ESCAPE = '\\',
		ENV = '$',
		PIPE_LINE = '|',
		REDIR_IN = '<',
		REDIR_OUT = '>',
		AND = '&',
		HERE_DOC,
		DREDIR_OUT,
	}type;
}t_token;
// executing
enum e_state
{
   IN_DQUOTE,
   IN_QUOTE,
   GENERAL,
};
typedef struct s_list
{
   char *env;
   char  *value;
   struct s_list *next;
   struct s_list *prev;
}t_list;

typedef struct s_lexer
{
   char *str;
   char **store;
   t_token *token;
   int i;
   struct s_lexer *next;
   struct s_lexer *prev;
}t_lexer;

// typedef struct s_elem
// {
//    char *content;
//    int len;
//    enum e_token type;
//    //enum
//    t_elem *next;
//    t_elem *prev;
// }t_elem;

char	**ft_split(char const *s, char c);
char	*ft_strdup(const char	*str);
size_t	ft_strlen(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
int	ft_isalpha(int c);
int ft_strchr(char *str,int c);

#endif