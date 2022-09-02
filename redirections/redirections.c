/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <youchenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 10:32:14 by youchenn          #+#    #+#             */
/*   Updated: 2022/09/02 10:56:59 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int out_redirection(char *file_path)
{
    int fd;

    fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror(file_path);
        return (-1);
    }
    if (dup2(fd, 1) < 0)
    {
        perror("duplicating fd error");
        return (-1);
    }
	if (close(fd) < 0)
	{
		perror("close");
		return (-1);
	}
    return (0);
}

int in_redirection(char *file_path)
{
    int fd;

    fd = open(file_path, O_RDONLY);
    if (fd < 0)
	{
        perror(file_path);
        return (-1);
	}
    if (dup2(fd, 0) < 0)
    {
        perror("duplicating fd error");
        return (-1);
    }
	if (close(fd) < 0)
	{
		perror("close");
		return (-1);
	}
    return (0);
}

int	append_redirection(char *file_path)
{
	int fd;

	fd = open(file_path, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd < 0)
	{
        perror(file_path);
        return (-1);
    }
    if (dup2(fd, 1) < 0)
    {
        perror("duplicating fd error");
        return (-1);
    }
	if (close(fd) < 0)
	{
		perror("close");
		return (-1);
	}
    return (0);
}

int	handel_redirections(t_command *cmd)
{
	t_redirection	*tmp;
	int				status;

	status = 0;
	tmp = cmd->redirections;
	while (tmp)
	{
		if (tmp->type == REDIR_LESSER
			|| tmp->type == DOUBLE_LESSER)
			status = in_redirection(tmp->f_name);
		else if (tmp->type == DOUBLE_GREATER)
			status = append_redirection(tmp->f_name);
		else if (tmp->type == REDIR_GREATER)
			status = out_redirection(tmp->f_name);
		if (status != 0)
			return (status);
		tmp = tmp->next;
	}
	return (status);
}