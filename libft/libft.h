/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbot <ybarbot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:25:45 by lauger            #+#    #+#             */
/*   Updated: 2024/05/24 12:25:00 by ybarbot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
size_t		ft_strlen(char const *str);
void		*ft_memset(void *dest, int c, size_t len);
void		ft_bzero(void *dest, size_t len);
void		*ft_memcpy(void *dest, void const *src, size_t len);
void		*ft_memmove(void *dest, void const *src, size_t len);
size_t		ft_strlcpy(char *dest, char const *src, size_t size);
size_t		ft_strlcat(char *dest, char const *src, size_t size);
int			ft_toupper(int c);
int			ft_tolower(int c);
char		*ft_strchr(char const *str, int c);
char		*ft_strrchr(char const *str, int c);
int			ft_strncmp(char const *s1, char const *s2, size_t n);
void		*ft_memchr(void const *src, int c, size_t len);
int			ft_memcmp(void const *src1, void const *src2, size_t len);
char		*ft_strnstr(const char *big, const char *little, size_t len);
int			ft_atoi(char const *str);
void		*ft_calloc(size_t nitems, size_t size);
char		*ft_strdup(char const *src);
int			ft_atoi_endptr(const char *str, char **endptr);
char		*ft_strjoinfree(char *s1, char const *s2);
void		ft_sort_int_tab(int *tab, int size);
void		ft_sort_string_tab(char **tab);
char		*ft_strstr(char *str, char *to_find);

/*#####################################
####PARTIE 2###########################
*///###################################

char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strjoin(char const *s1, char const *s2);
char		**ft_split(char const *s, char c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

/*#####################################
####PARTIE BONUS#######################
*///###################################

t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/*#####################################
####LIBFT##############################
*///###################################

int			ft_printf(const char *str, ...);
int			ft_putchar(char c);
int			ft_putnbr_base_len(unsigned long int nbr, char *base);
int			ft_putnbr_base_len_origin(int nbr, char *base);
int			ft_putstr_len(char *str);

/*#####################################
####En Plus############################
*///###################################

int			ft_atoi_base(char *str, char *base);
void		ft_free_tab(char **str);
int			ft_strlen_map(char **map);
char		**ft_strcpy_map(char **original, int height, int width);
long long	ft_atol(const char *str);
void		ft_free_lst(t_list *head);
char		*ft_strcpy(char *dest, const char *src);
char		*ft_strcat(char *dest, const char *src);
char		*ft_strncpy(char *dest, const char *src, size_t n);
char		*get_next_line_a(int fd);
int			ft_isspace(char c);
char		*ft_strndup(const char *src, size_t n);
void		*ft_realloc(void *ptr, size_t size, size_t oldsize);
size_t		ft_tab_len(char **tab);
char		**ft_copy_tab(char **tab);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_atoi_endptr(const char *str, char **endptr);

#endif
