/*
** match.c for 42sh in /home/jartho_d/42sh/mysh
** 
** Made by adrien1 jarthon
** Login   <jartho_d@epitech.net>
** 
** Started on  Fri May 23 17:26:04 2008 adrien1 jarthon
** Last update Mon Jun  2 03:44:30 2008 yoam farges
*/

#include "42sh.h"

char		undash(char c)
{
  return ((c == DASH) ? '-' : c);
}

int		add_range(char *pattern, char *index)
{
  char		c;

  if ((pattern[1] == DASH) && (pattern[2] != CLOSE_BRACKET))
    {
      c = undash(pattern[0]);
      while (c <= undash(pattern[2]))
	{
	  index[c + 128] = 1;
	  c++;
	}
      return (1);
    }
  else
    return (0);
}

char		*char_list(char *pattern, int end)
{
  char		index[256];
  char		*out;
  int		i;
  char		c;

  my_memset(index, 0, 256);
  i = 1;
  while (i < end)
    {
      if (add_range(pattern + i, (char *)index))
	i += 2;
      else
	index[undash(pattern[i]) + 128] = 1;
      i++;
    }
  out = xsmalloc(256);
  c = -128;
  i = 0;
  while (c++ < 127)
    if (index[c + 128])
      out[i++] = c;
  out[i] = 0;
  return (out);
}

int	range_match(char *str1, char *str2)
{
  char	*range;
  int	end;

  end = 0;
  while (str2[end] && (str2[end] != CLOSE_BRACKET))
    end++;
  if (!str2[end])
    return (0);
  range = char_list(str2, end);
  if (is_in(range, *str1))
    {
      xsfree(range);
      return (match(str1 + 1, is_in(str2, CLOSE_BRACKET) + 1));
    }
  xsfree(range);
  return (0);
}

int	match(char *str1, char *str2)
{
  if ((*str1 == '\0') && (*str2 == '\0'))
    return (1);
  if ((*str1 == '\0') && (*str2 == STAR))
    return (match(str1, str2 + 1));
  if (*str2 == HAT)
    return (!match(str1, str2 + 1));
  if (*str2 == OPEN_BRACKET)
    return (range_match(str1, str2));
  if ((*str1 != '\0') && ((undash(*str2) == *str1) || (*str2 == ANY)))
    return (match(str1 + 1, str2 + 1));
  if ((*str1 != '\0') && (*str2 == STAR))
    return (match(str1, str2 + 1) || match(str1 + 1, str2));
  return (0);
}
