/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:49:44 by saboulal          #+#    #+#             */
/*   Updated: 2023/10/03 13:41:13 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

int	is_env_name(char c)
{
	if (ft_tolower(c) || ft_toupper(c) || ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

int	handle_heredocs(t_mini *cmd, t_lexer *tokens, t_envp *env) // void
{
	int	status;

	while (tokens && tokens->type != PIPE_LINE)
	{
		if (tokens->type == HERE_DOC)
		{
			tokens = tokens->next;
			status = handle_heredoc(cmd, tokens->token, here_doc_name(), env);
			if (status)
				return (status);
		}
		else
			tokens = tokens->next;
	}
	return (1); // remove
}
