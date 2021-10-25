/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/28 13:42:48 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/07/19 20:53:37 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_dbllst
{
	int					index;
	int					num;
	struct s_dbllst		*next;
	struct s_dbllst		*prev;
}				t_dbllst;

int				ft_isupper(int c);
int				ft_islower(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);

void			*ft_memset(void *str, int c, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *str1, const void *str2, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			ft_bzero(void *str, size_t n);
void			*ft_calloc(size_t count, size_t size);

char			*ft_strdup(const char *s1);
size_t			ft_strlen(const char *str);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *str1, const char *str2, size_t n);
char			*ft_strnstr(const char *haystack,
					const char *needle, size_t len);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
void			free_split(char **split_array);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));

int				ft_atoi(const char *str);
char			*ft_itoa(int n);
float			ft_atof(char *str);

void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *str, int fd);
void			ft_putendl_fd(char *str, int fd);
void			ft_putnbr_fd(int n, int fd);

t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstclear(t_list **lst, void (*del)(void*));

t_dbllst		*ft_bdllist_new(int data);
void			ft_addfront_dbl_lst(t_dbllst **head, t_dbllst *new);
int				ft_dbllist_size(t_dbllst *head);
void			ft_addback_bdl_lst(t_dbllst **head, t_dbllst *new);
void			ft_clear_dbllst(t_dbllst **head);
void			ft_print_list(t_dbllst *head, char id);

#endif
