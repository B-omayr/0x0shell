/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <youchenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 08:39:31 by youchenn          #+#    #+#             */
/*   Updated: 2022/09/04 10:31:54 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_heredoc(int sig)
{
	if (sig != SIGINT)
		return ;
	close(0);
	g_global.skip = 1;
	return ;
}

void	heredoc_signal(void)
{
	signal(SIGINT, handle_heredoc);
	signal(SIGQUIT, SIG_IGN);
}
