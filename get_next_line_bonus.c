/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikorkut <ikorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:36:56 by ikorkut           #+#    #+#             */
/*   Updated: 2022/12/16 15:18:39 by ikorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_get_line(char *str)
{
	int		i;
	char	*line;
	int		new_line;

	i = 0;
	new_line = ft_strchr(str, '\n');
	if (!str[i])
		return (0);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * i + 1 + new_line);
	if (!line)
		return (0);
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_get_new_str(char *str)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	j = ft_strlen(str);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (0);
	}
	new_line = (char *)malloc(sizeof(char) * (j - i) + 1);
	if (!new_line)
		return (0);
	j = 0;
	i++;
	while (str[i] != '\0')
		new_line[j++] = str[i++];
	new_line[j] = '\0';
	free(str);
	return (new_line);
}

char	*ft_get_read(int fd, char *str)
{
	int		count;
	char	*now_str;

	now_str = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!now_str)
		return (0);
	count = 1;
	while (!ft_strchr(str, '\n') && count != 0)
	{
		count = read(fd, now_str, BUFFER_SIZE);
		if (count < 0)
		{
			free (now_str);
			return (0);
		}
		now_str[count] = '\0';
		str = ft_strjoin(str, now_str);
	}
	free (now_str);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str[256];
	char		*line;

	if (fd < 0 && BUFFER_SIZE <= 0)
		return (0);
	str[fd] = ft_get_read(fd, str[fd]);
	if (!str[fd])
		return (0);
	line = ft_get_line(str[fd]);
	str[fd] = ft_get_new_str(str[fd]);
	return (line);
}
/*
int	main(void)
{
	int		fd1 = open("a.txt", O_RDONLY);
	int		fd2 = open("b.txt", O_RDONLY);
	char	*a = get_next_line(fd1);
	char	*b = get_next_line(fd2);
	free(a);
	while (a)
	{
		printf("%s", a);
		a = get_next_line(fd1);
		free(a);
	}
	printf("%c", '\n');
	free(b);
	while (b)
	{
		printf("%s", b);
		b = get_next_line(fd2);
		free(b);
	}
	//system("leaks a.out");
}*/