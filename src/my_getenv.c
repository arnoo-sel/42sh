/*
** my_getenv.c for 42sh in /home/farges_y/link/42sh/mysh/src
** 
** Made by yoam farges
** Login   <farges_y@epitech.net>
** 
** Started on  Thu May 22 14:10:13 2008 yoam farges
** Last update Tue Jun 10 15:47:58 2008 yoam farges
*/

#include "42sh.h"

char	*my_getenv(t_env *env, char *str)
{
  int	idx;

  idx = 0;
  while ((env[idx].name != NULL) && (my_strcmp(env[idx].name, str) != 0))
    idx++;
  if (env[idx].name == NULL)
    return (0);
  return (env[idx].value);
}

char	*my_getvar(t_env *var, char *str)
{
  int	idx;

  idx = 0;
  while ((var[idx].name != NULL) && (my_strcmp(var[idx].name, str) != 0))
    idx++;
  if (var[idx].name == NULL)
    return (0);
  return (var[idx].value);
}
