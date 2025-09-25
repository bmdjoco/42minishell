/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:40:23 by milo              #+#    #+#             */
/*   Updated: 2025/07/10 12:01:15 by miltavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*next_line(char *stash)
{
	int				i;
	int				len;
	char			*next_stash;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	if (!stash[i])
		return (free(stash), NULL);
	len = ft_strlen(stash + i);
	if (len == 0)
		return (free(stash), NULL);
	next_stash = malloc(sizeof(char) * len + 1);
	if (!next_stash)
		return (free(stash), NULL);
	ft_strlcpy(next_stash, stash + i, len + 1);
	free(stash);
	return (next_stash);
}

int	size_calc(char *stash)
{
	int	i;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	return (i);
}

int	check_nl(char *stash)
{
	int	i;

	i = 0;
	if (!stash || !*stash)
		return (0);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		return (1);
	return (0);
}

char	*create_stash(int fd, char *stash)
{
	char		*tmp;
	char		*buff;
	ssize_t		bytes_r;

	while (!check_nl(stash))
	{
		buff = malloc(BUFFER_SIZE + 1);
		if (!buff)
			return (NULL);
		bytes_r = read(fd, buff, BUFFER_SIZE);
		if (bytes_r < 0)
			return (free(buff), free(stash), NULL);
		if (bytes_r == 0)
			return (free(buff), stash);
		buff[bytes_r] = '\0';
		tmp = ft_strjoin(stash, buff);
		free(buff);
		free(stash);
		stash = tmp;
		if (!stash)
			return (NULL);
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash[1024];
	int			line_size;

	if (fd == -42)
		return (cleanup(stash), NULL);
	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= 1024)
		return (NULL);
	stash[fd] = check_stash(stash[fd]);
	if (!stash[fd])
		return (NULL);
	stash[fd] = create_stash(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	if (!*stash[fd])
		return (free(stash[fd]), stash[fd] = NULL, NULL);
	line_size = size_calc(stash[fd]);
	line = malloc(sizeof(char) * (line_size + 1));
	if (!line)
		return (NULL);
	ft_strlcpy(line, stash[fd], line_size + 1);
	stash[fd] = next_line(stash[fd]);
	return (line);
}

// int	main(int argc, char **argv)
// {
// 	int			fd;
// 	char	*line;

// 	if (argc != 2)
// 		return (1);
// 	fd = open(argv[1], O_RDONLY);
// 	if (fd < 0)
// 		return (1);
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		printf("%s", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// 	return (0);
// }
