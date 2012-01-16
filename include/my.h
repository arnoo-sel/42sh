/*
** my.h for my_h in /u/epitech_2012/jartho_d/cu/rendu/include
** 
** Made by adrien1 jarthon
** Login   <jartho_d@epitech.net>
** 
** Started on  Thu Oct 11 10:17:14 2007 adrien1 jarthon
** Last update Fri Jun  6 11:05:33 2008 adrien1 jarthon
*/

#ifndef __MY_H__
# define __MY_H__

struct s_stock_par
{
  int  size_param;     /* longueur du parametre */
  char *str;           /* adresse du parametre  */
  char *copy;          /* copie du parametre    */
  char **tab;          /* renvoye par my_str_to_wordtab  */
};

typedef struct		s_alloc_addr
{
  void			*ptr;
  struct s_alloc_addr	*next;
}			t_alloc_addr;

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define OUT_BUFFER_SIZE	100000

void	my_putchar(char c);
int	my_isneg(int n);
int	my_put_nbr(int nb);
int	my_swap(int *a, int *b);
int	my_putstr(char *str);
int	my_strlen(char *str);
int	my_getnbr(char *str);
void	my_sort_int_tab(int *tab, int size);
int	my_power_rec(int nb, int power);
int	my_square_root(int nb);
int	my_is_prime(int nombre);
int	my_find_prime_sup(int nb);
char	*my_strcpy(char *dest, char *src);
char	*my_strncpy(char *dest, char *src, int n);
char	*my_revstr(char *str);  
char	*my_strstr(char *str, char *to_find);
int	my_strcmp(char *s1, char *s2);
int	my_stricmp(char *s1, char *s2);
int	my_strncmp(char *s1, char *s2, int n);
char	*my_strupcase(char *str);
char	*my_strlowcase(char *str);
char	*my_strcapitalize(char *str);
int	my_str_isalpha(char *str);
int	my_str_isnum(char *str);
int	my_str_islower(char *str);
int	my_str_isupper(char *str);
int	my_str_isprintable(char *str);
int	my_showstr(char *str);
int	my_showmem(unsigned char *str, int size);
char*	my_strcat(char *str1, char *str2);
char*	my_strncat(char *str1, char *str2, int n);
int	my_strlcat(char *str1, char *str2, int n);
char	*my_strdup(char *str);
int	is_printable(char c);
char	**my_str_to_wordtab(char *str);
int	my_putnbr_base(int nb, char *base, char *dest);
int	my_putnbr_base_stdout(int nb, char *base);
int	my_getnbr_base(char *str, char *base);
char	*convert_base(char *nbr, char *base_from, char *base_to);
int	is_big_endian(void);
struct s_stock_par      *my_param_to_tab(int ac, char **av);
int     my_show_tab(struct s_stock_par *par);
int     my_sort_wordtab(char **tab);
char	*is_in(char *str, char c);
char    **my_str_to_wordtab(char *str);
char    **my_str_to_wordtab_separator(char *str);
char    **my_str_to_wordtab_delimiter(char *str, char *cut);
int	get_nb_words(char *str);
int	get_nb_words_delimiter(char *str, char *cut);
int	get_nb_words_separator(char *str);
char    *sum_params(int argc, char **argv);
int	get_nb_words(char *str);
int	get_nb_words_separator(char *str);

int	my_printf(char *str, ...);
int	my_fprintf(int fd, char *str, ...);
int	my_putstr_printable(char *str);
int	my_put_unsigned_nbr(unsigned int nb, char* base);
int	my_put_signed_nbr(int nbr, char* base);
int	my_aff_int(va_list *va, char *base, int flags);
int	my_aff_uint(va_list *va, char *base, int flags);
int	my_aff_float(va_list *va, int flags);
int	set_font_color(int c);
int	set_back_color(int c);
void	*my_memset(void *mem, int c, int len);

char	*my_fgets(const int fd);
char	*my_sgets(const char* str, char stop);

char	*my_str_replace(char *str, char *del, char *add);
char	*my_char_replace(char *str, char c, char r);

void	*xmalloc(int size);

void	xfree(void *ptr);
int	mfree(void *ptr, ...);

void	*xsmalloc(int size);
int	xsfree(void *ptr);
int	msfree(void *ptr, ...);
int	xsfree_all();

#endif
