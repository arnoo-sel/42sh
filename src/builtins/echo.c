/*
** echo.c for 42sh in /u/epitech_2012/de-la-_o/cu/42sh_link/mysh/src/builtins
** 
** Made by jocelyn de-la-rosa
** Login   <de-la-_o@epitech.net>
** 
** Started on  Tue May  6 10:46:53 2008 jocelyn de-la-rosa
** Last update Thu May 29 12:51:27 2008 adrien1 jarthon
*/

#include "42sh.h"

int	b_echo(t_param *param, char **cmd)
{
  int	id;
  int	n;

  param = param;
  n = 0;
  id = 0;
  if ((cmd[1] != NULL) && !(my_strcmp(cmd[1], "-n")))
    {
      n = 1;
      id = 1;
    }
  while (cmd[++id])
    {
      if (!(((id == 2) && (n == 1)) || ((id == 1) && ( n == 0))))
	my_putstr(" ");
      my_putstr(cmd[id]);
    }
  if (!n)
    my_putstr("\n");
  return (0);
}
