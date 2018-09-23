/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrealjoin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robert0 <fripponsupersonique@42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 20:38:19 by robert0           #+#    #+#             */
/*   Updated: 2018/09/23 20:44:44 by robert0          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<stdlib.h>
#include	<string.h>
#include	"libft.h"

/*
** ft_strrealjoin: like ft_strjoin but instead of allocate a new char
**				   it reallocate s1
*/
char	*ft_strrealjoin(char *s1, const char *s2)
{
	char	*ret;

	ret = NULL;
	if ((s1 != NULL) && (s2 != NULL))
	{
		ret = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1);
		if (ret != NULL)
		{
			ft_strcpy(ret, s1);
			ft_strcpy((ret + ft_strlen(s1)), s2);
			free(s1);
		}
	}

	return (ret);
}

