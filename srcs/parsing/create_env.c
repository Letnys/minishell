/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:20:08 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/03/09 19:46:53 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*find_string(char *str)
{
	int		len;

	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	if (str[len])
		len++;
	return (ft_substr(str, len, (ft_strlen(str) + 1) - len));
}

static char	*find_pref(char *str)
{
	int		len;

	len = 0;
	while (str[len] != '=')
		len++;
	return (ft_substr(str, 0, len));
}

t_env	*create_node(char *str)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	node->next = NULL;
	node->string = find_string(str);
	node->pref = find_pref(str);
	node->full_string = ft_strdup(str);
	return (node);
}

void	create_env(char **envp, t_env **env)
{
	t_env	*new_node;
	t_env	*cursor;

	while (*envp != NULL)
	{
		new_node = create_node(*envp);
		if (*env == NULL)
			*env = new_node;
		else
		{
			cursor = *env;
			while (cursor->next != NULL)
				cursor = cursor->next;
			cursor->next = new_node;
		}
		envp++;
	}
}
