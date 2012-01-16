/*
** get_subs.c for 42sh in /home/farges_y/link/42sh/mysh/src/history
** 
** Made by yoam farges
** Login   <farges_y@epitech.net>
** 
** Started on  Sun Jun  1 23:20:17 2008 yoam farges
** Last update Sun Jun  1 23:21:02 2008 yoam farges
*/

#include "42sh.h"

char	*get_subs_hist(char *str, int i)
{
  int	save;
  char	*subs;

  save = i;
  i++;
  while (endsubs(str[i]) == 0)
    i++;
  subs = xsmalloc(sizeof(*subs) * (i - save));
  my_memset(subs, 0, (i - save));
  i = (save + 1);
  save = -1;
  while (endsubs(str[i]) == 0)
    {
      subs[++save] = str[i];
      i++;
    }
  return (subs);
}

char	*get_interrog_subs(char *str, int i)
{
  int	save;
  char	*subs;

  save = i;
  i += 2;
  while ((str[i] != 0) && (str[i] != '?'))
    i++;
  subs = xsmalloc(sizeof(*subs) * (i - save - 1));
  my_memset(subs, 0, (i - save - 1));
  i = (save + 1);
  save = -1;
  while ((str[++i] != 0) && (str[i] != '?'))
    subs[++save] = str[i];
  return (subs);
}
