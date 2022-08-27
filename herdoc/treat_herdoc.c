/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_herdoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 16:32:16 by iomayr            #+#    #+#             */
/*   Updated: 2022/08/27 16:35:20 by iomayr           ###   ########.fr       */
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
        
        // printf(">>\n%s\n",file_name);
		free(tmp);
		if (access(file_name, F_OK))
			return (file_name);
		free(file_name);
		i += 1;
		if (i > 2147483647)
		{
			tmp = part1;
			part1 = ft_strjoin(part1, "_");
			free(tmp);
			i = 0;
		}
	}
}

char	*traite_herdoc(char *del)
{
	int		fd;
	char	*line;
	char	*available_name;

	available_name = get_available_name();
	fd = open(available_name, O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (fd < 0)
		return (NULL);
	while (1)
	{
		line = readline("herdoc> ");
		
		if (!line || !ft_strncmp(del, line, ft_strlen(del) + 1))
		{
			close(fd);
			free(line);
			return (available_name);
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	if (close(fd) < 0)
		return (NULL);
	return (available_name); 
}