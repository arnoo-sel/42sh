/*
** free.c for 42sh in /u/epitech_2012/de-la-_o/cu/42sh_link/mysh/src/builtins
** 
** Made by jocelyn de-la-rosa
** Login   <de-la-_o@epitech.net>
** 
** Started on  Tue May  6 10:35:35 2008 jocelyn de-la-rosa
** Last update Thu May 22 16:08:57 2008 adrien1 jarthon
*/

#include "42sh.h"

int	free_env(t_env *env)
{
  int	id;

  id = -1;
  while (env[++id].name)
    {
      xsfree(env[id].name);
      if (env[id].value != NULL)
	xsfree(env[id].value);
    }
  xsfree(env);
  return (0);
}

int	free_cmd(char **cmd)
{
  int	id;

  id = -1;
  while (cmd[++id])
    xsfree(cmd[id]);
  xsfree(cmd);
  return (0);
}
