/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellma.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 12:19:30 by claudioca         #+#    #+#             */
/*   Updated: 2018/06/09 02:19:50 by gfloure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shellma.h>
#include <unistd.h>
#include <mysh.h>
#include <globbing.h>
#include <ft_printf.h>
#include <stdio.h>


#include "libft.h"

typedef struct			s_fd
{
	int					fd_n;
	int					lastbuff;
	void				*tampon;
	struct s_fd			*next;
}						t_fd;

typedef struct			s_parts_chars
{
	size_t				i;
	size_t				start;
	size_t				count;
	size_t				is_c;
}					t_parts_chars;

/*
** 1 regarde si dans le tampon il y a une /n
** 		si oui renvoie la partie de la ligne avec \n et stoque un pointeur de
** l'endroit d'arret puis fin de la fonction.
** 2 si non lit la premiere boucle colle le resultat avec le tampon(s'il y a)
** free le tampon
**		puis regarde dans la boucle si il y a un \n
**		si oui, renvoie la partie de la ligne avec un \n et stoque l'endroit ou
** il s'est arreter puis fin de la fonction.
**		la string devient le tampon
*/

int			memfind(void *str, size_t len)
{
	size_t		i;

	i = 0;
	if (len != 0 && (((char *)str)[i] == '\n' || ((char *)str)[i] == 26))
		i++;
	while (i < len && ((char *)str)[i] != '\n' && ((char *)str)[i] != 26)
	{
		if (((char *)str)[i] == '\n' || ((char *)str)[i] == 26)
			break ;
		i++;
	}
	if (i == len)
		return (0);
	return (i);
}

int			verif(char **line, void *string, int len, t_fd *mail)
{
	int		i;
	int		j;
	void	*tampon;

	i = 0;
	j = 0;
	while (((char *)string)[i] != '\n' && ((char *)string)[i] != 26 && i < len)
		i++;
	if (!(*line = ft_memalloc(sizeof(char) * i + 1)))
		return (-1);
	while (i > j)
	{
		line[0][j] = ((char *)string)[j];
		j++;
	}
	if (!(tampon = ft_memalloc(len - j + 1)))
		return (-1);
	if (((char *)string)[j] == '\n' || ((char *)string)[j] == 26)
		j++;
	mail->lastbuff = 0;
	while (j < len)
		((char *)tampon)[mail->lastbuff++] = ((char *)string)[j++];
	mail->tampon = tampon;
	free(string);
	return (1);
}

int			concat(t_fd *mail, void **buff, int *j)
{
	void	*tmp;
	int		i;

	i = *j;
	if (!(tmp = ft_memalloc(sizeof(char) * mail->lastbuff + i + 1)))
		return (-1);
	if (mail->tampon)
	{
		ft_memcpy(tmp, mail->tampon, mail->lastbuff + 1);
		free(mail->tampon);
	}
	ft_memcpy(&tmp[mail->lastbuff], buff[0], i + 1);
	mail->lastbuff = mail->lastbuff + i;
	mail->tampon = tmp;
	return (0);
}

int			read_my_line(t_fd *mail, char **line)
{
	int		i;
	void	*buff;

	if (memfind(mail->tampon, mail->lastbuff) > 0)
		return (verif(line, mail->tampon, mail->lastbuff, mail));
	i = BUFF_SIZE;
	if (!(buff = ft_memalloc(sizeof(char) * BUFF_SIZE + 1)))
		return (-1);
	while (i == BUFF_SIZE)
	{
		if ((i = read(mail->fd_n, buff, BUFF_SIZE)) < 1 && mail->lastbuff == 0)
			break ;
		if (concat(mail, &buff, &i) == -1)
			return (-1);
		if (i != BUFF_SIZE || memfind(mail->tampon, mail->lastbuff) > 0)
		{
			free(buff);
			return (verif(line, mail->tampon, mail->lastbuff, mail));
		}
	}
	free(buff);
	return (0);
}

int			ft_gnl(const int fd, char **line)
{
	static t_fd		*begin = NULL;
	t_fd			*list;
	t_fd			*mail;

	if (fd < 0 || !line || (line[0] = NULL) != NULL || read(fd, *line, 0) == -1)
		return (-1);
	list = begin;
	while (list && list->next && list->fd_n != fd)
		list = list->next;
	if (!list || list->fd_n != fd)
	{
		mail = malloc(sizeof(t_fd));
		mail->next = NULL;
		mail->tampon = NULL;
		mail->fd_n = fd;
		mail->lastbuff = 0;
		if (!begin)
			begin = mail;
		else
			list->next = mail;
		return (read_my_line(mail, line));
	}
	return (read_my_line(list, line));
}

/*
** process_backtits("echo `echo salut`")
** return "echo salut"
*/

char		*ft_strreplace(char *origin, char *piece, size_t pos, size_t len)
{
	char *debut;
	char *millieu;
	char *fin;

	debut = ft_memdup(origin, pos);
//	ft_printf("Début : '%s'\n", debut);
	millieu = piece;
//	ft_printf("Millieu : '%s'\n", millieu);
	fin = ft_strdup(origin + len + 1);
//	ft_printf("Fin : '%s'\n", fin + 1);
	return (ft_vjoin(3, debut, millieu, fin));
}


void		dellines(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			str[i] = ' ';
		i++;
	}
}

char 		*backtits_replace(char *str)
{
	char 	*start;
	char	*stop;
	char	*exec;
	int		p[2];
	int		out;
	char    print[1024];

	start = ft_strchr(str, '`');
	if (!start)
		return (str);
	if(!(stop = ft_strchr(start + 1, '`')))
		return (str); // Error !
	exec = ft_memdup(start + 1, stop - start - 1);
		out = dup(1);
	pipe(p);
	dup2(p[1], 1);
	close(p[1]);
	execute(parse(lex(exec)));
	close(1);

	print[read(p[0], print, 1023)] = '\0';
	read(p[0], print, 1023); 
	dup2(out, 1);
	close(p[0]);
	close(out);

	dellines((char*)print);

	return (ft_strreplace(str, (char*) print, start - str, stop - str));
}


/*
 ** Centralized executor
 ** @return program status
 */

int			process_input(char *str)
{
	int		return_value;
	char	*input;

	str = alias_replace(str);
	if ((input = deglob(str, NULL, NULL, NULL, NULL)) == NULL)
	{
		free(str);
		return (ft_printf("42sh: No matchs found.\n"));
	}
	input = alias_replace((char *)input);
	input = backtits_replace(input);
	return_value = execute(parse(lex(input)));
	str ? ft_strdel(&str) : 0;
	input ? free(input) : 0;
	return (return_value);
}
