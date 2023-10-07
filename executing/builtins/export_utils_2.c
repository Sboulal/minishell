/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 22:45:34 by saboulal          #+#    #+#             */
/*   Updated: 2023/10/07 10:00:18 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	check_unset_env(char *cmd)
{
	int	i;

	i = 1;
	if (!(ft_isalpha(cmd[0]) || cmd[0] == '_'))
	{
		g_var.sig_status = 1;
		return (0);
	}
	while (cmd[i])
	{
		if (!(ft_isalpha(cmd[0]) || cmd[0] == '_'))
		{
			g_var.sig_status = 1;
			return (0);
		}
		i++;
	}
	return (1);
}

char	**my_split_word(char *cmd, char c)
{
	int		i;
	char	**str;
	char	*tmp;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == c)
			break ;
		i++;
	}
	if (cmd[i])
	{
		str = (char **)malloc(sizeof(char *) * 3);
		tmp = cmd;
		str[0] = ft_substr(tmp, 0, i);
		str[1] = ft_substr(tmp, i + 1, ft_strlen(tmp));
		str[2] = NULL;
		return (str);
	}
	str = (char **)malloc(sizeof(char *) * 2);
	str[0] = ft_substr(cmd, 0, ft_strlen(cmd));
	str[1] = NULL;
	return (str);
}

char	**list_clean(char *cmd, int num)
{
	char	**str;
	char	**src;
	char	*tmp1;
	int		i;

	i = 0;
	str = my_split_word(cmd, '='); 
	if (!(*str))
		return (NULL);
	if (num == 2)
	{
		tmp1 = str[0];
		src = my_split_word(tmp1, '+');
		str[0] = ft_strdup(src[0]);
		while (src[i])
			free(src[i++]);
		free(tmp1);
		free(src);
	}
	return (str);
}

int	check_export(char *cmd)
{
	int	i;

	i = 0;
	if (check_error_export(cmd, i) == 0)
		return (0);
	while (cmd[i] && cmd[i] != '=')
	{
		if (cmd[i + 1] && cmd[i] == '+' && cmd[i + 1] == '=')
			return (2);
		else if (cmd[i] == '+')
		{
			check_export_err(cmd);
			return (0);
		}
		if (!(ft_isalpha(cmd[0]) || cmd[0] == '_') && (!(i != 0 && cmd[i + 1]
					&& ft_isalpha(cmd[i - 1]) && cmd[i] == '+' && cmd[i + 1])))
		{
			check_export_err(cmd);
			return (0);
		}
		i++;
	}
	if (!check_before_equal(cmd))
		return (0);
	return (1);
}

int	check_unset(char *cmd)
{
	int	i;

	i = 1;
	if (!(ft_isalpha(cmd[0]) || cmd[0] == '_'))
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		g_var.sig_status = 1;
		return (0);
	}
	while (cmd[i])
	{
		if (!(ft_isalpha(cmd[0]) || cmd[0] == '_'))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_var.sig_status = 1;
			return (0);
		}
		i++;
	}
	return (1);
}
