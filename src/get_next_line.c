/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npizzi <npizzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:03:39 by npizzi            #+#    #+#             */
/*   Updated: 2024/09/02 19:18:19 by npizzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	int			i;
	int			reminder_bytes;
	static char	reminder[BUFFER_SIZE + 1];
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	line = NULL;
	if (reminder[0] != 0)
	{
		i = 0;
		reminder_bytes = 0;
		while (reminder[reminder_bytes] != 0)
			reminder_bytes++;
		line = malloc(reminder_bytes + 1);
		if (line == NULL)
			return (NULL);
		while (i <= reminder_bytes)
		{
			line[i] = reminder[i];
			reminder[i++] = 0;
		}
	}
	line = create_line(&line, reminder, fd);
	return (line);
}
