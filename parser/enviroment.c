/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:49:44 by saboulal          #+#    #+#             */
/*   Updated: 2023/10/07 02:21:09 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_env_name(char c)
{
	if (ft_tolower(c) || ft_toupper(c) || ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

int	handle_heredocs(t_mini *cmd, t_lexer *tokens, t_envp *env)
{
	while (tokens && tokens->type != PIPE_LINE)
	{
		if (tokens->type == HERE_DOC)
		{
			tokens = tokens->next;
			handle_heredoc(cmd, tokens->token, here_doc_name(), env);
		}
		else
			tokens = tokens->next;
	}
	return (1);
}

void	cmd_repl_nor(t_mini **cmd, t_list	**list)
{
	(*cmd)->cmd = ft_strdup((*list)->content);
	(*cmd)->next = NULL;
	(*list) = (*list)->next;
}

t_list	*cmd_repl(t_lexer *tokens, t_mini **cmd, int *i)
{
	t_list	*list;
	t_list	*tmp;
	t_list	*list_head;

	list = cmd_list(tokens);
	tmp = list;
	if (list)
		cmd_repl_nor(cmd, &list);
	else
	{
		(*cmd)->cmd = NULL;
		(*cmd)->next = NULL;
	}
	if (list)
	{
		list_head = list;
		while (list_head)
		{
			list_head = list_head->next;
			(*i)++;
		}
	}
	list = tmp;
	return (list);
}

t_mini	*arg_repl(t_list *list, int i, t_mini **cmd)
{
	t_list	*list_head;
	int		j;

	j = 0;
	if (list)
	{
		(*cmd)->arg = (char **)malloc(sizeof(char *) * (i + 1));
		if (!(*cmd)->arg)
			return ((*cmd));
		list_head = list->next;
		while (list_head)
		{
			(*cmd)->arg[j] = ft_strdup((char *)list_head->content);
			list_head = list_head->next;
			j++;
		}
		(*cmd)->arg[j] = NULL;
	}
	else
		(*cmd)->arg = NULL;
	return (NULL);
}
