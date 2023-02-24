/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:51:04 by egeorgel          #+#    #+#             */
/*   Updated: 2023/02/24 01:54:00 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc(t_data *data, char *sep)
{
	int		fd[2];
	char	*str;

	if (pipe(fd) == -1)
		error(ERR_MAX, NULL, data);
	str = readline("heredoc> ");
	while (!ft_strcmp(str, sep))
	{
		ft_putstr_fd(str, fd[1]);
		str = readline("heredoc> ");
	}
	close(fd[1]);
	data->in_fd = realloc_fd(fd[0], data->in_fd);
}

void	redirect_fd(t_data *data, char *symbol, char *file)
{
	if (ft_strcmp(symbol, ">>"))
		data->out_fd = realloc_fd(open(file, O_CREAT | O_RDWR
					| O_APPEND, 000644), data->out_fd);
	else if (ft_strcmp(symbol, ">"))
		data->out_fd = realloc_fd(open(file, O_CREAT | O_RDWR
					| O_TRUNC, 000644), data->out_fd);
	else if (ft_strcmp(symbol, "<<"))
		heredoc(data, file);
	else if (ft_strcmp(symbol, "<"))
		data->in_fd = realloc_fd(open(file, O_RDONLY), data->in_fd);
	if (last_fd(data->in_fd) == -1 || last_fd(data->out_fd) == -1)
		error(ERR_FD, file, data);
}

void	get_redirection_out(t_data *data)
{
	char	*str;
	char	**out;
	char	*buf;

	str = ft_startincharset(data->prompt, "<>");
	while (data->prompt && str)
	{
		out = sep_input(str);
		if (!out[1])
			error(ERR_EMPTYREDIRECTION, NULL, data);
		redirect_fd(data, out[0], out[1]);
		ft_strrem(data->prompt, out[0]);
		ft_strrem(data->prompt, out[1]);
		ft_freetab((void **)out);
		printf("> '%s'\n", data->prompt);
		printf("> '%s'\n", str);
		if (data->prompt)
			str = ft_startincharset(str, "<>");
	}
	if (data->prompt)
	{
		buf = ft_strtrim(data->prompt, "\t\n\v\f\r ");
		free (data->prompt);
		data->prompt = buf;
	}
}
