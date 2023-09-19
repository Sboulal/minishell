/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:43:09 by saboulal          #+#    #+#             */
/*   Updated: 2023/09/19 23:37:50 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../headers/lexer.h"

int	get_name_len(char *token, int i)
{
	int	name_len;

	if (token[i + 1] == '?')
		return (2);
	if (!(ft_toupper(token[i + 1]) || ft_tolower(token[i + 1])
			|| token[i + 1] == '_'))
		return (0);
	name_len = 1;
	while (is_env_name(token[i + 1]))
	{
		i++;
		name_len++;
	}
	return (name_len);
}

t_lexer	*remove_empty_tokens(t_lexer *tokens, t_lexer *head, t_lexer *prev)
{
	while (tokens)
	{
		if (*(tokens->token) == 0)
		{
			if (prev == NULL)
			{
				head = tokens->next;
				free_token_word(tokens, tokens->token);
				tokens = head;
			}
			else
			{
				prev->next = tokens->next;
				free_token_word(tokens, tokens->token);
				tokens = prev->next;
			}
		}
		else
		{
			prev = tokens;
			tokens = tokens->next;
		}
	}
	return (head);
}

char	*get_name_here(char *token)
{
	int	i;
	int	name_len;

	i = 0;
	name_len = -1;
	while (token[i])
	{
		name_len = -1;
		if (token[i] == '$')
			name_len = get_name_len(token, i);
		if (name_len == 0)
			token[i] = -1;
		if (name_len > 0)
			break ;
		i++;
	}
	if (name_len == 0 || name_len == -1)
		return (NULL);
	return (ft_substr(token, i, i + name_len));
}

int	replace_before_name_here(char *new_token, char *token)
{
	int	i;

	i = 0;
	while (token[i] != '$')
	{
		new_token[i] = token[i];
		i++;
	}
	return (i);
}
char	*replace_name_value(char *token, char *name, char *value)
{
	char	*new_token;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	new_token = ft_calloc(ft_strlen(token)
			+ (ft_strlen(value) - ft_strlen(name)) + 1);
	i = replace_before_name_here(new_token, token);
	k = i;
	j = 0;
	while (value[j])
	{
		if (value[j] == '$')
			value[j] = -1;
		new_token[i++] = value[j++];
	}
	k += ft_strlen(name);
	while (token[k])
		new_token[i++] = token[k++];
	free(token);
	return (new_token);
}

char	*get_env_value(char *name, t_envp *env)
{
	t_envp	*tmp;

	if (!name)
		return (NULL);
	tmp = env;
	if (!tmp)
		return (NULL);
	// if (*name == '?')
	// 	return (ft_itoa(g_var.status));
	while (tmp)
	{
		if (!ft_strcmp(tmp->variable, name))
		{
			if (tmp->value)
				return (tmp->value);
			return (NULL);
		}
		tmp = tmp->next;
	}
	return (NULL);
}


int	contains_expand(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!is_identifier(s[i]))
			return (i);
		i++;
	}
	return (0);
}
int number_word_ident(char *token)
{
	int i;
	int len;
	int wc;

	i = 0;
	wc = 0;
	len = 0;
	if(!token)
		return(0);
	while (token[i])
	{
		if(is_identifier(token[i]))
			i++;
		else
			return (i);
	}
	return (i);
}
// char	*get_name(char **token)
// {
// 	int	i;
// 	int	name_len;
// 	int	dbl_quote;
// 	i = 0;
// 	name_len = -1;
// 	dbl_quote = -1;
// 	while (token[i])
// 	{
// 		name_len = -1;
// 		if (token[i] == '"')
// 			dbl_quote *= -1;
// 		if (token[i] == '\'' && dbl_quote == -1)
// 			i = next_quote(i + 1, token[i], token);
// 		if (token[i] == '$')
// 			name_len = get_name_len(token, i);
// 		if (name_len == 0)
// 			token[i] = -1;
// 		if (name_len > 0)
// 			break ;
// 		i++;
// 	}
// 	if (name_len == 0 || name_len == -1)
// 		return (NULL);
// 	return (ft_substr(token, i, i + name_len));
// }

char find_for_expand(char *token)
{
	int j;

	if (!token)
		return (*token);
	j = 0;
	while (token[j])
	{
		if (token[j] == '"')
			return (token[j]);
		if (token[j] == '\'')
			return (token[j]);
		if (token[j] == '$')
			return (token[j]);
		(j)++;
	}
	return (token[j]);
}
char *find_dollar_double(char **token, int *i, t_envp *env)
{
	int len;
	char *str;
	char *value;
	int j;
	
	j = 0;
	if (!(*token))
		return (NULL);
	len = (*i);
	str = ft_strdup("");
	while (token[*i])
	{
		if (token[*i][0] == '$')
		{
			value = get_env_value(token[*i] + 1, env);
			if (value)
				str = ft_strjoin(str, value);
		}
		if (token[*i][0] != '"')
				str = ft_strjoin(str, token[*i]);
		(*i)++;
		if (token[*i] && token[*i][0] == '"')
		{
			if (token[*i][1])
			{
				while (token[*i][j])
					j++;
				str = ft_strjoin(str, ft_substr(token[*i], 1, j));
			}
			(*i)++;
			break ;
		}
	}
	return(str);
}
char *find_dollar_singal(char **token, int *i)
{
	int j;
	char *str;

	j = 0;
	if (!(*token))
		return (NULL);
	while (token[*i])
	{
		(*i)++;
		str = ft_strjoin(str, token[*i]);
		if (token[*i] && token[*i][0] == '\'')
		{
			if (token[*i][1])
			{
				while (token[*i][j])
					j++;
				str = ft_strjoin(str, ft_substr(token[*i], 1, j));
			}
			break ;
		}
	}
	return (str);
}

char	*parameter_expansion(char **token, t_envp *env)
{
	int		i;
	int		j;
	int		k;
	char	*value;
	t_list *list;
	char *s;
	
	
	i = 0;
	j = 0;
	if (!(*token))
		return (NULL);
	list = ft_lstnew("");
	k = 0;
	while (token[i])
	{
		if (find_for_expand(token[i]) == '"')
			ft_lstadd_back(&list, ft_lstnew(find_dollar_double(token, &i, env)));
		else if (find_for_expand(token[i]) == '\'')
			ft_lstadd_back(&list, ft_lstnew(find_dollar_singal(token, &i)));
		else if (find_for_expand(token[i]) == '$')
		{
			value = get_env_value(token[i] + 1, env);
			if (value)
				ft_lstadd_back(&list, ft_lstnew(value));
			i++;
		}
		else
		{
			ft_lstadd_back(&list, ft_lstnew(token[i]));
			i++;
		}
	}
	i = 0;
	s = ft_strdup("");
	while (list)
	{
		s = ft_strjoin(s, list->content);
		list = list->next;
	}
	return (free(token), s);
}
// char	*parameter_expansion(char **token, t_envp *env)
// {
// 	int		i;
// 	char **str;
// 	int		j;
// 	int		k;
// 	char	*value;
// 	t_list *list;
// 	char *s;
	
	
// 	i = 0;
// 	j = 0;
// 	if (!(*token))
// 		return (NULL);
// 	while (token[j])
// 		j++;
// 	// str = (char **)malloc(sizeof(char *) * (j + 1));
// 	if (!str)
// 		return (NULL);
// 	k = 0;
// 	while (token[i])
// 	{
// 		if (find_for_expand(token[i]) == '"')
// 			str = find_dollar_double(token, &i, env);
// 		else if (find_for_expand(token[i]) == '\'')
// 			str = find_dollar_singal(token, &i);
// 		else if (find_for_expand(token[i]) == '$')
// 		{
// 			value = get_env_value(token[i] + 1, env);
// 				printf("*************ha ana %s %d\n", token[i], i);
// 			if (value)
// 				str[k++] = ft_strdup(value);
// 			i++;
// 		}
// 		else
// 		{
// 			printf("ha ana %s %d\n", token[i] , i);
// 			str[k++] = ft_strdup(token[i]);
// 			i++;
// 		}
// 	}
// 	i = 0;
// 	s = ft_strdup("");
// 	while (i < j && str[i])
// 	{
// 		s = ft_strjoin(s, str[i]);
// 		i++;
// 	}
// 	return ( s);
// }
