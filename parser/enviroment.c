/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:49:44 by saboulal          #+#    #+#             */
/*   Updated: 2023/09/13 14:07:27 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../lexer.h"

int	is_env_name(char c)
{
	if (ft_tolower(c) || ft_toupper(c) || ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

int	handle_heredocs(t_mini *cmd, t_lexer *tokens)
{
	int	status;

	while (tokens && tokens->type != PIPE_LINE)
	{
		if (tokens->type == HERE_DOC)
		{
			tokens = tokens->next;
			status = handle_heredoc(cmd, tokens->token, here_doc_name());
			if (!status)
				return (status);
		}
		else
			tokens = tokens->next;
	}
	return (1);
}
