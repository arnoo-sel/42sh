/*
** path.c for 42sh in /home/jartho_d/42sh/mysh/src
** 
** Made by adrien1 jarthon
** Login   <jartho_d@epitech.net>
** 
** Started on  Mon May  5 11:55:23 2008 adrien1 jarthon
** Last update Fri Jun 13 13:08:53 2008 yoam farges
*/

#include "42sh.h"

int		find_path_var(t_env *env)
{
  int		id_path;

  id_path = 0;
  while (env[id_path].name)
    {
      if (my_strcmp(env[id_path].name, "PATH") == 0)
	return (id_path);
      id_path++;
    }
  return (-1);
}

char		*get_path_str(char *env_path, int i)
{
  int		pos;
  char		*out;

  if (!(*env_path))
    return (0);
  if (i)
    {
      while ((*env_path) && (*(env_path++) != ':'));
      return (get_path_str(env_path, i - 1));
    }
  else
    {
      pos = -1;
      while ((env_path[++pos]) && (env_path[pos] != ':'));
      out = xsmalloc(pos + 1);
      my_strncpy(out, env_path, pos);
      out[pos] = 0;
      return (out);
    }
  return (0);
}

char		*get_next_path(t_env *env)
{
  int		id_path;
  static int	path = 0;
  char		*str;

  if (!env)
    {
      path = 0;
      return (0);
    }
  if ((id_path = find_path_var(env)) == -1)
    return (0);
  if ((str = get_path_str(env[id_path].value, path++)))
    return (str);
  path = 0;
  return (0);
}
