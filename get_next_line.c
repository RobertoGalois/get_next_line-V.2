/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robert0 <fripponsupersonique@42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 17:45:47 by robert0           #+#    #+#             */
/*   Updated: 2018/09/23 22:59:02 by robert0          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h


/*
** get_correct_file: select t_list file that is related to the fd
**                   if it doesn't exist, it push front a new t_list related to the
**                   fd and return it.
*/
static t_list_openedfd	*get_correct_file(t_list_openedfd **file, int fd)
{
	t_list_openedfd		*tmp;

	tmp = *file;
	while (tmp != NULL)
	{
		if ((tmp->fd) == fd)
			return (tmp);

		tmp = tmp->next;
	}

	tmp = (t_list_openedfd *)(ft_memalloc(sizeof (t_list_openedfd)));
	if (tmp == NULL)
		return (NULL);

	tmp->fd = fd;
	tmp->remain_str = ft_strdup("\0");
	ft_lstadd((t_list **)(file), (t_list*)(tmp));

	return (tmp);
}

/*
** ft_dupuntil: takes a & char *dst, allocate memory and put the chars
**				 from src until it meets a \0 or c
**				 returns the number of chars copyied without the \0
**				 or -1 if there were an error
*/
static int		ft_dupuntil(char **dst, char *src, char c)
{
	size_t	indx;

	indx = 0;
	while ((src[indx] != '\0') && (src[indx] != c))
		indx++;

	if ((*dst = ft_strnew(indx)) == NULL)
		return (-1);

	ft_strncpy(*dst, src, indx);
	return (indx);
}

/*
** ft_shiftstr: takes an char* and an index_from and shift all the chars
**				from indx_from to indx_to (indx_from < indx_to)
*/
void		ft_shiftstr(char *str, size_t indx_from)
{
	size_t	indx_to;

	indx_to = 0;
	while (str[indx_from] != '\0')
	{
		str[indx_to] = str[indx_from];
		indx_to++;
		indx_from++;
	}

	str[indx_to] = '\0';
}

/*
** ft_lstremoveat: remove the list that ties in the fd, and relink extremities
*/
static void	ft_lstremoveat(t_list_openedfd **list, int fd)
{
	t_list_openedfd		*prev;
	t_list_openedfd		*temp;

	prev = NULL;
	temp = *list;
	while (temp != NULL)
	{
		if (temp->fd == fd)
		{
			if (prev == NULL)
				*list = temp->next;

			else if (temp->next == NULL)
				prev->next = NULL;

			else
				prev->next = temp->next;

			ft_memdel((void **)(&(temp->remain_str)));
			ft_memdel((void **)(&temp));
			break;
		}

		prev = temp;
		temp = temp->next;
	}
}

/*
** get_next_line: you know what to do
**				  At first I absolutely wanted to have a
**				  static buf[BUFF_SIZE + 1] and get the remaning
**				  chars at the begining of the function.
**				  but if we called the function with differents fd,
**                the remaining chars were related to the previous fd.
**				  So I preferred to use a t_list to save the remaining chars
*/
int		get_next_line(const int fd, char **line)
{
	char						buf[BUFF_SIZE + 1];
	static t_list_openedfd		*file;
	t_list_openedfd				*curr_file;
	int							i;
	int							ret;

	/*
	** ft_check_params
	*/
	if ((fd < 0 || line == NULL || read(fd, buf, 0) < 0))
		return (-1);

	curr_file = get_correct_file(&file, fd);
	ft_memdel((void **)(line));
	if ((*line = ft_strnew(0)) == NULL)
		return (-1);

	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if ((curr_file->remain_str = ft_strrealjoin(curr_file->remain_str, buf)) == NULL)
			return (-1);

		if (ft_strchr(buf, '\n'))
			break ;
	}

	/*
	** if we have reach the EOF and there's no chars left in the buffer,
	*/
	if ((ret < BUFF_SIZE) && (ft_strlen(curr_file->remain_str) == 0))
	{
		/*
		** we remove and free the t_list from the list
		*/
		ft_lstremoveat(&file, fd);

		return (0);
	}

	/*
	** we copy in *line all the chars from remain_str before the \n
	*/
	if ((i = ft_dupuntil(line, curr_file->remain_str, '\n')) == -1)
		return (-1);

	/*
	** if there are some chars left in remain_str, we shift.
	** we could have realloc but it's some check to do.
	*/
	if (i < ((int)(ft_strlen(curr_file->remain_str))))
		ft_shiftstr(curr_file->remain_str, (size_t)(i + 1));

	/*
	** if not, we free the memory and set to NULL
	*/
	else
		ft_memdel((void **)(&(curr_file->remain_str)));

	return (1);
}
