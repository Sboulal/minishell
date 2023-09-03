/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 11:10:14 by saboulal          #+#    #+#             */
/*   Updated: 2023/09/02 13:31:39 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"lexer.h"

static int	check_line(char *str,char charc)
{
	int	i;
	int	c;

	i = 0;
	while (str[i])
	{
		if (str[i] == QOUTE)
		{	i++;
			while (str[i] && str[i] != QOUTE)
				i++;
		}
		if (str[i] == DOUBLE_QOUTE)
		{
			i++;
			while (str[i] && str[i] != DOUBLE_QOUTE)
				i++;
		}
		if (str[i] == charc)
			c++;
		if (str[i])
			i++;
	}
	return (c);
}

int check_paren(char *str)
{
	
}

int is_line_synx_valid(char *str)
{
	int	i;

	i = 0;
	if(chek_line(str,'(') != check_line(str,')'))
		return(0);
	while(str[i])
	{
		if(str[i] == QOUTE)
		{
			i++;
			if(str[i] != QOUTE)
			{
				while(str[i])
					i++;
			}
		}
		if(str[i] == DOUBLE_QOUTE)
		{
			i++;
			if(str[i] != DOUBLE_QOUTE)
			{
				while(str[i])
				i++;
			}
		}
		if(str[i] == '(')
			if()
		
	}
}