/*
** setprompt.c for setprompt in /home/farges_y/link/42sh/mysh/src/builtins
** 
** Made by yoam farges
** Login   <farges_y@epitech.net>
** 
** Started on  Tue Jun 10 13:50:13 2008 yoam farges
** Last update Tue Jun 10 13:57:40 2008 yoam farges
*/

#include "42sh.h"

int	b_setprompt(t_param *param, char **cmd)
{
  int	len;

  len = 0;
  while (cmd[len] != NULL)
    len++;
  if (len == 0);
  else if (len == 1)
    my_printf("setprompt: Too few arguments.");
  else if (len > 2)
    my_printf("setprompt: Too many arguments.");
  else
    {
      if (param->prompt_conf != NULL)
	xsfree(param->prompt_conf);
      param->prompt_conf = my_strdup(cmd[1]);
    }
  return (0);
}
