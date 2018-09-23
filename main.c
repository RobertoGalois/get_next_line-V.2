/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robert0 <fripponsupersonique@42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 18:21:22 by robert0           #+#    #+#             */
/*   Updated: 2018/09/23 14:35:50 by robert0          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<sys/types.h>
#include	<sys/stat.h>
#include	<fcntl.h>
#include	<unistd.h>
#include	"libft.h"
#include	"get_next_line.h"

void	ft_putline(int fd, char **line)
{
	get_next_line(fd, line);
	ft_putendl(*line);
}

int		main(int argc, char **argv)
{
	int		fd;
	char	buf[30];
	char	*line;


	line = NULL;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd != -1)
		{
			int		ret;

			while ((ret = get_next_line(fd, &line)) > 0)
			{
				ft_putendl(line);
			}

			close(fd);
		}
		else
		{
			ft_putendl("Error while opening the file.");
		}
	}

	else
		ft_putendl("Usage: ./test_gnl [fileName]");

	return (0);
}
