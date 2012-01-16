/*
** tild.c for 42sh in /u/epitech_2012/de-la-_o/cu/42sh_link/mysh/src/globing
** 
** Made by jocelyn de-la-rosa
** Login   <de-la-_o@epitech.net>
** 
** Started on  Fri May 30 16:29:11 2008 jocelyn de-la-rosa
** Last update Thu Jun  5 11:17:59 2008 jocelyn de-la-rosa
*/

#include "42sh.h"

int	replace_tild(t_param *param, t_cmd *cmd)
{
  int	i;
  char	*home;
  char	*path;

  i = -1;
  while (cmd->arg[++i])
    {
      my_memset(param->inhib, 4, my_strlen(cmd->arg[i]) + 1);
      if ((cmd->arg[i][0] == '~') &&
	  (!is_inhibited(cmd->arg[i], param->inhib, 0)))
	{
	  if ((home = my_getenv(param->env, "HOME")) == 0)
	    {
	      my_printf("%s: No home directory.\n", cmd->arg[0]);
	      return (1);
	    }
	  path = xsmalloc(sizeof(*path) * (my_strlen(cmd->arg[i])
					   + my_strlen(home)));
	  my_strcpy(path, home);
	  my_strcat(path, (cmd->arg[i] + 1));
	  cmd->arg[i] = path;
	}
    }
  return (0);
}
