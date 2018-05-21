/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/09 09:25:06 by ccabral           #+#    #+#             */
/*   Updated: 2018/05/21 14:58:24 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <unistd.h>
# define BUFF_SIZE 1337
# define ZERO_IF_FAIL(x) if ((x) == 0) return (0)

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

typedef int		(*t_predf)(void *iterator, void const *data);
typedef void	(*t_applyf)(void *element, void *args);
typedef void	*(*t_applyf_until)(void *element, void *args);
typedef int		(*t_cmpf)(void const *, void const *);
typedef void	(*t_freef)(void *element);
typedef int		(*t_cpyf)(void *dst, void const *src, void *args);

void			noop(void *any);
t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstpush_back(t_list **lst, void const *content,
												size_t content_size);
void			ft_lstdelone(t_list **alst,
					void (*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **lst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void			ft_lstprepend(t_list **addr,
						t_list *lst);
t_list			*ft_xlstnew(const void *cnt,
						size_t cnt_size);
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
char			**ft_strsplit(char const *str, char c);
char			*ft_concat_params(int argc, char **argv);
char			*ft_itoa(int nb);
char			*ft_strcapitalize(char *str);
char			*ft_strcat(char *dest, const char *src);
char			*ft_strchr(const char *s, int c);
char			*ft_strcpy(char *dest, const char *src);
char			*ft_strdup(const char *src);
char			*ft_strndup(const char *src, size_t size);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strlowcase(char *str);
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_strncat(char *dest, const char *src, size_t nb);
char			*ft_strncpy(char *dest, const char *src, int len);
char			*ft_strnew(size_t size);
char			*ft_strnstr(const char *big, const char *little, size_t len);
char			*ft_strrchr(const char *s, int c);
char			*ft_strrev(char *str);
char			*ft_strstr(const char *big, const char *little);
char			*ft_strsub(const char *s, unsigned int start, size_t len);
char			*ft_strtrim(char const *s);
char			*ft_strtok(char *foo, const char *bar);
char			*ft_strupcase(char *str);
int				offsetcmp(const char *s1,
					const char *s2,
					char *tmp1,
					char *tmp2);
void			ft_bzero(void *s, size_t n);
int				ft_max(const int a, const int b);
int				ft_atoi(const char *str);
int				ft_atoi_base(const char *str, const char *base);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_iterative_power(int nb, int power);
int				ft_putchar(int c);
int				ft_sqrt(int nb);
int				ft_str_is_alnum(const char *str);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strcmp_until(const char *s1, const char *s2, char c);
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
size_t			ft_strlen(const char *str);
int				ft_strncmp(const char *s1, const char *s2, unsigned int n);
int				ft_tolower(int c);
int				ft_toupper(int c);
int				ft_ultimate_range(int **range, int min, int max);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
size_t			ft_realloc(void **buffer, size_t old_size,
													size_t new_size);
unsigned int	ft_strlcat(char *dest, const char *src, size_t size);
unsigned int	ft_strlcpy(char *dest, const char *src, unsigned int size);
void			*ft_memalloc(size_t size);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memset(void *b, int c, size_t len);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
void			ft_memdel(void **ap);
void			ft_print_words_tables(const char **table);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl(char const *s);
void			ft_putendl_fd(char const *s, int fd);
void			ft_puterror(const char *err);
void			ft_putnbr(int nb);
void			ft_putnbr_base(int nbr, const char *base);
void			ft_putnbr_fd(int nb, int fd);
void			ft_putstr(const char *str);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putstr_non_printable(const char *str);
void			ft_strclr(char *s);
void			ft_strdel(char **as);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
void			ft_swap(void *a, void *b, void *buffer, size_t size);
int				ft_partition(void **array, int low, int high, t_cmpf cmpf);
void			ft_quicksort(void **array, int low, int high, t_cmpf cmpf);
int				ft_nbr_digits(int nbr);
int				ft_is_whitespace(int c);
size_t			ft_next_power_of_two(size_t value);
void			free_wrapper(void **ptr);
void			*median(void *begin, void *end, size_t size);
int				ft_strdup_wrapper(char **dst, char const *const *src,
															void *dummy);
int				ft_strncmp_wrapper(char const **a, char const **b);
int				ft_strcmp_wrapper(char const **a, char const **b);
void			ft_freejoin(const char **s1, const char **s2, char c);
char			*ft_strjoinfree(char const *s1, char const *s2, char c);
char			*ft_strnjoin(char const *s1, char const *s2, size_t n, char c);
int				get_next_line(int fd, char **line);
int				ft_cpy_ptr(void **dst, void **src, void *dummy);

typedef enum	e_bool
{
	FALSE = 0,
	TRUE
}				t_bool;

#endif
