/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:43:09 by saboulal          #+#    #+#             */
/*   Updated: 2023/09/20 13:26:44 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../headers/lexer.h"
int is_identifier(char c)
{
	if (!c)
		return (0);
	if (isalnum(c) || c == '_')
		return (1);
	return (0);
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
char	*get_env_value(char *name,t_envp *env)
{
	t_envp	*tmp;

	tmp = env;
	if (*name == '?')
		return (ft_itoa(g_var.status));
	if (!tmp)
		return (NULL);
	while (tmp)
	{
		if (!ft_strcmp(tmp->variable, name))
		{
			if (tmp->value)
				return (tmp->value);
			return ("");
		}
		tmp = tmp->next;
	}
	return ("");
}
// this function returns the len of the variable name , exp : $abc => 4 , $ => 1
// [A-Z]{1,}[A-Z0-9_]
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

// this function returns the first occurence of a variable name 
// if we have an occurence of a $ alone we just mark it with -1 
// to not interump with further calls to this function
// we will change the -1 latter
char	*get_name(char *token,t_envp *env)
{
	int	i;
	int	name_len;
	int	dbl_quote;
    (void)env;
	i = 0;
	name_len = -1;
	dbl_quote = -1;
	while (token[i])
	{
		name_len = -1;
		if (token[i] == '"')
			dbl_quote *= -1;
		if (token[i] == '\'' && dbl_quote == -1)
			i = next_quote(i + 1, token[i], token);
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

// we need to check if the variable is not inside double quotes to 
// not expand it , but check if we don't have double quotes before 
int	replace_before_name(char *new_token, char *token)
{
	int	i;
	int	dbl_quotes;
	int	sgl_quotes;

	dbl_quotes = 0;
	sgl_quotes = 0;
	i = 0;
	while (token[i] != '$' || sgl_quotes)
	{
		if (token[i] == '\'' && !dbl_quotes)
			sgl_quotes = !sgl_quotes;
		if (token[i] == '"')
			dbl_quotes = !dbl_quotes;
		new_token[i] = token[i];
		i++;
	}
	return (i);
}

// this function remplace the string value in the string
// name and returns an allocated string
// we add one the len of name bc it doesn't contain the '$' char
// (token[i] != '$' || j == 1) , it means while we are before an unquoted $
char	*replace_name_value(char *token, char *name, char *value)
{
	char	*new_token;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	if(!token || !name || !value)
		return(NULL);
	new_token = ft_calloc(ft_strlen(token)
			+ (ft_strlen(value) - ft_strlen(name)) + 1);
	i = replace_before_name(new_token, token);
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

// this funtion search for variable name and replace it by its value recursivly
char	*parameter_expansion(char *token,t_envp *env)
{
	char	*name;
	char	*value;
	char	*new_token;

	name = get_name(token, env);
	if (!name)
	{
		expands_dollars_dollars(token);
		return (token);
	}
	value = get_env_value(name + 1,env);
	new_token = replace_name_value(token, name, value);
	if (*(name + 1) == '?')
		free(value);
	free(name);
	return (parameter_expansion(new_token,env));
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
