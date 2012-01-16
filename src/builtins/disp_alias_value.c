/*
** disp_alias_value.c for 42sh in /u/epitech_2012/de-la-_o/cu/42sh_link/mysh/src
** 
** Made by jocelyn de-la-rosa
** Login   <de-la-_o@epitech.net>
** 
** Started on  Thu Jun 12 11:42:56 2008 jocelyn de-la-rosa
** Last update Thu Jun 12 11:54:30 2008 jocelyn de-la-rosa
*/

#include "42sh.h"

void	disp_alias_value(t_param *param, char *alias)
{
  int	id;

  id = -1;
  while (param->alias[++id].name)
    {
      if (!my_strcmp(param->alias[id].name, alias))
	{
	  my_printf("%s\n", param->alias[id].value);
	  return;
	}
    }
}
