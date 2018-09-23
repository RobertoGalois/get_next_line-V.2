/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robert0 <fripponsupersonique@42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 18:14:35 by robert0           #+#    #+#             */
/*   Updated: 2018/09/23 14:42:13 by robert0          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		__GET_NEXT_LINE_H__
 #define	__GET_NEXT_LINE_H__

 #define	BUFF_SIZE	32
 #define	CHECK(x) if (!x) return (-1)

 #include	<stdlib.h>
 #include	<unistd.h>
 #include	"libft.h"

 typedef struct				s_list_openedfd
 {
	char					*remain_str;
	int						fd;
	struct s_list_openedfd	*next;
 }							t_list_openedfd;

 int	get_next_line(const int fd, char **line);

#endif
