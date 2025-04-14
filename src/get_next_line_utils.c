/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npizzi <npizzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:55:45 by niccol            #+#    #+#             */
/*   Updated: 2024/09/02 19:18:16 by npizzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_handler(char *line, char *buffer)
{
	if (line != NULL)
		free(line);
	if (buffer != NULL)
		free(buffer);
	return (NULL);
}

char	*append_buffer(char *line, char *buffer, int bytes_read)
{
	int		i;
	int		line_bytes;
	char	*new_buffer;

	line_bytes = 0;
	i = 0;
	while (line != NULL && line[line_bytes] != 0)
		line_bytes++;
	if (bytes_read < 0 || (line_bytes + bytes_read) <= 0)
		return (free_handler(line, buffer));
	new_buffer = malloc(bytes_read + line_bytes + 1);
	if (new_buffer == NULL)
		return (free_handler(line, buffer));
	while (line != NULL && i++ < line_bytes)
		new_buffer[i - 1] = line[i - 1];
	i = 0;
	while (buffer != NULL && i++ < bytes_read)
		new_buffer[line_bytes + (i - 1)] = buffer[i - 1];
	new_buffer[line_bytes + (i - 1)] = 0;
	free_handler(line, buffer);
	return (new_buffer);
}

int	check_for_n(char **line, char *reminder)
{
	int	i;
	int	x;

	if (*line == NULL)
		return (0);
	i = 0;
	while ((*line)[i] != 0)
	{
		if ((*line)[i++] == '\n')
		{
			x = 0;
			while ((*line)[i + x] != 0)
			{
				reminder[x] = (*line)[i + x];
				x++;
			}
			*line = append_buffer(NULL, *line, i);
			return (1);
		}
	}
	return (0);
}

char	*create_line(char **line, char *reminder, int fd)
{
	char	*buffer;
	int		bytes_read;

	while (check_for_n(line, reminder) == 0)
	{
		buffer = malloc(BUFFER_SIZE);
		if (buffer == NULL)
			return (free_handler(*line, buffer));
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		*line = append_buffer(*line, buffer, bytes_read);
		if (*line == NULL)
			return (NULL);
		if (bytes_read == 0)
			return (*line);
	}
	return (*line);
}
