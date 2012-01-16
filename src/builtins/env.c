/*
** env.c for env in /home/farges_y/link/42sh/mysh/src/builtins
** 
** Made by yoam farges
** Login   <farges_y@epitech.net>
** 
** Started on  Tue May  6 10:38:38 2008 yoam farges
** Last update Thu Jun  5 13:58:28 2008 jocelyn de-la-rosa
*/

#include "42sh.h"

int	b_env(t_param *param, char **cmd)
{
  int	id;

  cmd = cmd;
  id = -1;
  while (param->env[++id].name != NULL)
    {
      if (param->env[id].value == NULL)
	my_printf("%s=\n", param->env[id].name);
      else
	my_printf("%s=%s\n", param->env[id].name, param->env[id].value);
    }
  return (0);
}
