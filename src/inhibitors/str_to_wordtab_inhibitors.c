/*
** my_str_to_wordtab.c for my_str_to_wordtab in /u/epitech_2012/jartho_d/cu/rendu/piscine/Jour_08
** 
** Made by adrien1 jarthon
** Login   <jartho_d@epitech.net>
** 
** Started on  Wed Oct 10 11:02:03 2007 adrien1 jarthon
** Last update Thu Jun  5 11:13:07 2008 jocelyn de-la-rosa
*/

#include "42sh.h"

char	*is_in_str(char **cut, char *str, char *inhib, int pos)
{
  int	id;

  id = -1;
  while (cut[++id])
    {
      if ((!(my_strncmp(str + pos, cut[id], my_strlen(cut[id])))) &&
	  (!str_is_inhibited(str, inhib, pos, (pos + my_strlen(cut[id])))))
	return (cut[id]);
    }
  return (0);
}

int	get_nb_words_inhibitors(char *str, char *inhib, char **cut)
{
  int	i;
  int	num;
  char	*c;

  num = 0;
  i = 0;
  while ((str[i] != '\0') && ((c = is_in_str(cut, str, inhib, i)) != 0))
    i += my_strlen(c);
  while (str[i] != '\0')
    {
      num++;
      while ((str[i] != '\0') && !(is_in_str(cut, str, inhib, i)))
	  i++;
      while ((str[i] != '\0') && (c = is_in_str(cut, str, inhib, i)))
	i += my_strlen(c);
    }
  return (num);
}

char	**my_str_to_wordtab_light(char *str, char **cut)
{
  char	*inhib;
  char	**t;

  inhib = xsmalloc(sizeof(*inhib) * (my_strlen(str) + 1));
  my_memset(inhib, 4, my_strlen(str) + 1);
  t = my_str_to_wordtab_inhibitor(str, inhib, cut);
  xsfree(inhib);
  return (t);
}

char	**init_tab(char *str, char *inhib, char **cut)
{
  char	**out;
  int	num;

  is_inhibited(str, inhib, my_strlen(str));
  num = get_nb_words_inhibitors(str, inhib, cut);
  out = xsmalloc(sizeof(*out) * (num + 1));
  return (out);
}

char	**my_str_to_wordtab_inhibitor(char *str, char *inhib, char **cut)
{
  char	**out;
  int	i;
  int	num;
  char	*c;

  i = 0;
  while ((str[i] != '\0') && ((c = is_in_str(cut, str, inhib, i)) != 0))
    i += my_strlen(c);
  out = init_tab(str, inhib, cut);
  num = 0;
  while (str[i] != '\0')
    {
      out[num] = &str[i];
      num++;
      while ((str[i] != '\0') && !is_in_str(cut, str, inhib, i))
	  i++;
      while ((str[i] != '\0') && (c = is_in_str(cut, str, inhib, i)))
	{
	  str[i] = '\0';
	  i += my_strlen(c);
	}
    }
  out[num] = 0;
  xsfree(cut);
  return (out);
}
