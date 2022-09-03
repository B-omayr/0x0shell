/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_herdoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 16:32:16 by iomayr            #+#    #+#             */
/*   Updated: 2022/09/03 10:28:35 by iomayr           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_available_name(void)
{
	char	*part1;
	char	*tmp;
	char	*file_name;
	long	i;

	part1 = ft_strdup("/tmp/.here_doc");
	i = 0;
	while (1)
	{
		tmp = ft_itoa(i);
		file_name = ft_strjoin(part1, tmp);
        
		//free(tmp);
		if (access(file_name, F_OK))
			return (file_name);
		//free(file_name);
		i += 1;
		if (i > 2147483647)
		{
			tmp = part1;
			part1 = ft_strjoin(part1, "_");
			//free(tmp);
			i = 0;
		}
	}
}

char	*traite_herdoc(char *del, t_main *v_main)
{
	int		fd;
	char	*line;
	char	*available_name;

	available_name = get_available_name();
	fd = open(available_name, O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (fd < 0)
		return (NULL);
	heredoc_signal();
	while (!g_global.skip)
	{
		line = readline("herdoc> ");
		if (!line || !ft_strncmp(del, line, ft_strlen(del) + 1))
		{
			close(fd);
			free(line);
			return (available_name);
		}
		if (search_for_dollar(line) && v_main->cmd->is_delimter_in_quotes)
			expand_dollar(&line, v_main);
		ft_putendl_fd(line, fd);
		free(line);
	}
	if (close(fd) < 0)
		return (NULL);
	return (available_name); 
}