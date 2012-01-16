/*
** is_inhibited.c for 42sh in /u/epitech_2012/de-la-_o/cu/42sh_link/mysh/src/inhibitors
** 
** Made by jocelyn de-la-rosa
** Login   <de-la-_o@epitech.net>
** 
** Started on  Fri May 23 17:37:55 2008 jocelyn de-la-rosa
** Last update Sun Jun  1 23:33:33 2008 jocelyn de-la-rosa
*/

#include "42sh.h"

int	is_between_quote(char *str, char *i, int pos)
{
  int	ini;
  int	s_q;
  int	d_q;

  s_q = 0;
  d_q = 0;
  ini = -1;
  while (++ini < pos)
    {
      if ((str[ini] == '\'') && !is_inhibited(str, i, ini) && !s_q)
	s_q = 1;
      else if ((str[ini] == '\'') && !is_inhibited(str, i, ini) && s_q && !d_q)
	s_q = 0;
      else if ((str[ini] == '\"') && !is_inhibited(str, i, ini) && !d_q)
	d_q = 2;
      else if ((str[ini] == '\"') && !is_inhibited(str, i, ini) && d_q && !s_q)
	d_q = 0;
      else
	is_inhibited(str, i, ini);
    }
  if (s_q && (str[ini] != '\''))
    return (1);
  else if (d_q && (str[ini] != '"'))
    return (2);
  return (0);
}

int	is_inhibited(char *str, char *inhib, int pos)
{
  int	ini;
  int	bs;
  int	j;

  j = 0;
  bs = 0;
  ini = pos - 1;
  if (pos == 0)
      return (inhib[pos] = 0);
  if (inhib[pos] != 4)
      return ((int)inhib[pos]);
  if ((str[ini] == '\\') && (!is_inhibited(str, inhib, ini)))
    return (inhib[pos] = 3);
  if (((inhib[pos] = is_between_quote(str, inhib, pos)) == 2) &&
      (str[pos] == '$'))
    inhib[pos] = 0;
  return ((int)inhib[pos]);
}

int	check_quote(char *str, char *inhib)
{
  char	c;
  int	last;
  int	ini;

  c = 0;
  last = my_strlen(str);
  if ((ini = is_inhibited(str, inhib, last)))
    {
      if (ini == 1)
	c = '\'';
      else if (ini == 2)
	c = '"';
      else if (ini == 3)
	c = '\\';
      my_fprintf(2, "Unmatched %c.\n", c);
      return (1);
    }
  return (0);
}

char	**clear_inhib_str(char *str)
{
  char	*inhib;
  char	**clear;
  int	i;
  int	len;

  i = -1;
  clear = xsmalloc(sizeof(*clear) * 2);
  inhib = xsmalloc(sizeof(*inhib) * (my_strlen(str) + 1));
  clear[0] = xsmalloc(sizeof(*clear[0]) * (my_strlen(str) + 1));
  clear[1] = xsmalloc(sizeof(*clear[1]) * (my_strlen(str) + 1));
  my_memset(inhib, 4, my_strlen(str) + 1);
  is_inhibited(str, inhib, my_strlen(str));
  len = 0;
  while (str[++i])
    if (((str[i] == '\'') || (str[i] == '"') || (str[i] == '\\')) &&
	(!is_inhibited(str, inhib, i)));
    else
      {
	clear[0][len] = str[i];
	clear[1][len] = inhib[i];
	len++;
      }
  clear[0][len] = 0;
  xsfree(inhib);
  return (clear);
}

int	str_is_inhibited(char *str, char *inhib, int start, int end)
{
  while (start <= end)
    {
     if (is_inhibited(str, inhib, start))
	return (1);
      start++;
    }
  return (0);
}
