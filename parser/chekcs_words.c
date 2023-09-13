/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chekcs_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 20:24:58 by saboulal          #+#    #+#             */
/*   Updated: 2023/09/13 17:25:36 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/lexer.h"

// static char	*get_next_word(char *s, int *index)
// {
// 	int		i;
// 	int		j;
// 	int		k;
// 	char	*word;

// 	k = 0;
// 	i = *index;
// 	while ((s[i] == ' ' || s[i] == '\t') && s[i])
// 		i++;
// 	j = i;
// 	while (!(s[i] == ' ' || s[i] == '\t') && s[i])
// 		i++;
// 	word = ft_calloc(i - j + 1);
// 	while (j < i)
// 	{
// 		word[k] = s[j];
// 		k++;
// 		j++;
// 	}
// 	*index = i;
// 	return (word);
// }


// t_lexer	*word_spliting(t_lexer *token)
// {
// 	char	**words;
// 	int		wc;
// 	int		i;

// 	wc = word_split_count(token->token);
// 	if (wc == 1 || wc == 0)
// 		return (token);
// 	words = my_split(token->token, wc);
// 	free(token->token);
// 	token->token = words[0];
// 	i = 1;
// 	while (words[i])
// 	{
// 		add_middle(token, words[i]);
// 		token = token->next;
// 		i++;
// 	}
// 	free(words);
// 	return (token);
// }