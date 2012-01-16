/*
** verify_pipe_redirless.c for verifie in /home/farges_y/link/42sh/mysh
** 
** Made by yoam farges
** Login   <farges_y@epitech.net>
** 
** Started on  Tue May  6 17:07:30 2008 yoam farges
** Last update Thu Jun  5 11:08:42 2008 arnaud sellier
*/

#include "42sh.h"

int	quit_verifpiperedir(void)
{
  my_printf("%s", BAD_P);
  return (-1);
}

int	verify_pipe_redirless(char *str)
{
  int	id;
  int	stat;
  int	stat2;
  char	*inhib;

  inhib = xmalloc((strlen(str) + 1) * sizeof(*inhib));
  memset(inhib, 4, (strlen(str) + 1));
  id = stat = stat2 =0;
  while (str[id] != 0)
    {
      if ((is_inhibited(str, inhib, id) == 0) && (str[id] == '|'))
        stat = 1;
      else if ((str[id] != ' ') && (str[id] != '\t'))
        stat = 2;
      if ((stat == 1) && ((stat2 == 0) || (stat2 == 1) || (stat2 == 3)))
        return (quit_verifpiperedir());
      if (stat == 1)
        stat = 3;
      stat2 = stat;
      id++;
    }
  xfree(inhib);
  if ((stat == 3) || (stat == 0))
    return (quit_verifpiperedir());
  return (1);
}
