/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:49:39 by saboulal          #+#    #+#             */
/*   Updated: 2023/10/07 11:28:02 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/exec.h"

char	*get_word(char *s, size_t *index)
{
	size_t	i;
	int		pos;
	size_t	len;

	i = *index;
	pos = position_of_operator(&s[i]);
	len = 0;
	if (pos == -1)
	{
		len = ft_strlen(&s[i]);
		*index += len;
		return (ft_substr(&s[i], 0, len));
	}
	if (pos == 0)
	{
		while (is_operator(s[i + len]))
			len++;
		*index += len;
		return (ft_substr(&s[i], 0, len));
	}
	*index += pos ;
	return (ft_substr(&s[i], 0, pos));
}

t_lexer	*skip_op(char **string)
{
	t_lexer	*tokens;
	size_t	i;
	size_t	j;
	char	*token;

	i = 0;
	tokens = NULL;
	while (string[i])
	{
		j = 0;
		while (string[i][j])
		{
			token = get_word(string[i], &j);
			add_back(&tokens, token);
			free(token);
		}
		i++;
	}
	return (tokens);
}

t_lexer	*parse_norm(char *str)
{
	char	**string;
	t_lexer	*lexer;

	string = skip_vid(str);
	if (string == NULL)
	{
		g_var.sig_status = 258;
		ft_putstr_fd("minishell:", 2);
		ft_putstr_fd(" syntax error near unexpected token", 2);
		ft_putstr_fd("\n", 2);
		tabfree(string);
		return (NULL);
	}
	lexer = skip_op(string);
	tabfree(string);
	add_ambg(&lexer);
	return (lexer);
}

void	error_print(void)
{
	g_var.sig_status = 258;
	ft_putstr_fd("minishell:", 2);
	ft_putstr_fd(" syntax error near unexpected token", 2);
	ft_putstr_fd("\n", 2);
}

t_mini	*parse(char *str, t_envp *env)
{
	t_mini	*mini;
	t_lexer	*lexer;
	t_lexer	*head;
	int		i;

	lexer = parse_norm(str);
	if (!check_parse(lexer))
	{
		error_print();
		free_tokens(lexer);
		return (NULL);
	}
	token_herdoc(lexer);
	head = lexer;
	i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	lexer = expand_lexer(lexer, env);
	mini = convert_to_cmds(lexer, env);
	return (mini);
}
