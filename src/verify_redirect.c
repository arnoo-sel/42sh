/*
** verify_redirect.c for 42sh in /u/epitech_2012/sellie_a/cu/42sh/mysh
** 
** Made by arnaud sellier
** Login   <sellie_a@epitech.net>
** 
** Started on  Tue May  6 11:32:33 2008 arnaud sellier
** Last update Fri Jun 13 14:58:51 2008 adrien1 jarthon
*/

#include "42sh.h"

int	file_at_right(char *str, int pos, char c)
{
  int	i;

  i = pos;
  while (str[i] == c)
    i++;
  if ((str[i] == 0) || (str[i] == '\n'))
    {
      my_putstr(MISS_NAME);
      return (0);
    }
  while ((str[i] == ' ') || (str[i] == '\t'))
    i++;
  if ((str[i] == 0) || (str[i] == '\n') || (n_is_char_in_str(str[i], "><|")))
    {
      my_putstr(MISS_NAME);
      return (0);
    }
  return (1);
}

int	verify_r1(char *s, char c, int *sr)
{
  char	*inhib;

  inhib = xmalloc((strlen(s) + 1) * sizeof(*inhib));
  memset(inhib, 4, (strlen(s) + 1));
  if ((s[0] == c) && (is_inhibited(s, inhib, 0) == 0) && (s[1] != c))
    {
      if (file_at_right(s, 0, c))
	(*sr)++;
      else
	{
	  FREE_RETURN(inhib, 0);
	}
    }
  else if ((strlen(s) > 1) && (s[0] == c) && (is_inhibited(s, inhib, 0) == 0)
	   && (s[1] == c) && (s[2] != c))
    {
      if (file_at_right(s, 0, c))
	(*sr)++;
      else
	{
	  FREE_RETURN(inhib, 0);
	}
    }
  FREE_RETURN(inhib, 1);
}

int	verify_r2(char *s, char c, int *sr, int i)
{
  char	*inhib;

  inhib = xmalloc((strlen(s) + 1) * sizeof(*inhib));
  memset(inhib, 4, (strlen(s) + 1));
  if ((s[i] == c) && (is_inhibited(s, inhib, i) == 0) && (s[i + 1] != c) &&
      (s[i - 1] != c))
    {
      if ((file_at_right(s, i, c)) && (((*sr)++) || 1));
      else
	{
	  FREE_RETURN(inhib, 0);
	}
    }
  else if ((my_strlen(s) > (i + 1)) && (s[i] == c) && (s[i - 1] != c) &&
	   (is_inhibited(s, inhib, i) == 0) && (s[i + 1] == c)
	   && (s[i + 2] != c))
    {
      if (file_at_right(s, i, c))
	(*sr)++;
      else
	{
	  FREE_RETURN(inhib, 0);
	}
    }
  FREE_RETURN(inhib, 1);
}

int	verify_r(char *s, char c, char *err)
{
  int	sr;
  int	i;

  sr = 0;
  i = 0;
  while (s[i])
    {
      if (i == 0)
	{
	if (!verify_r1(s, c, &sr))
	  return (0);
	}
      else if (i)
	{
	  if (!verify_r2(s, c, &sr, i))
	    return (0);
	}
      i++;
    }
  if (sr > 1)
    {
      my_putstr(err);
      return (0);
    }
  return (1);
}
