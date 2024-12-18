/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luestira <luestira@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 20:01:06 by luestira          #+#    #+#             */
/*   Updated: 2024/12/10 17:06:43 by luestira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read_fd(int fd, char *buffer)
{
	char	*new_buffer;
	int		nb_read;

	new_buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	nb_read = 1;
	if (!new_buffer)
		return (free(buffer), buffer = NULL, NULL);
	while (nb_read > 0 && !ft_strchr(buffer, '\n'))
	{
		nb_read = read(fd, new_buffer, BUFFER_SIZE);
		if (nb_read > 0)
		{
			new_buffer[nb_read] = '\0';
			buffer = ft_strjoin(buffer, new_buffer);
		}
	}
	free(new_buffer);
	if (nb_read < 0)
		return (free(buffer), buffer = NULL, NULL);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	buffer[fd] = ft_read_fd(fd, buffer[fd]);
	if (!buffer[fd])
		return (free(buffer[fd]), buffer[fd] = NULL, NULL);
	line = ft_read_line(buffer[fd]);
	if (!line)
		return (free(buffer[fd]), buffer[fd] = NULL, NULL);
	buffer[fd] = ft_new_line(buffer[fd]);
	return (line);
}
/*int	main(void)
{
	int		fd[2];
	char	*line;
	int		count;
	int		i;

	i = 0;
	fd[0] = open("1.txt", O_RDONLY);
	fd[1] = open("2.txt", O_RDONLY);
	if (fd[i] < 0)
		return (0);
	count = 0;
	while (i < 2)
	{
		line = "";
		while ((line = get_next_line(fd)) != NULL)
		{
			printf("LINE [%d] - %s", count, line);
			count++;
			free(line);
		}
		i++;
	}
	close(*fd);
	return (0);
}*/
