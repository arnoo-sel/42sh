/*
** history_subs.c for 42sh in /home/farges_y/cunix/42sh/mysh
** 
** Made by yoam farges
** Login   <farges_y@epitech.net>
** 
** Started on  Wed May 28 08:41:22 2008 yoam farges
** Last update Sun Jun  1 23:22:14 2008 yoam farges
*/

#include "42sh.h"

int	launch_hist(t_param *param, char *subs, int i)
{
  if ((subs[0] >= '0') && (subs[0] <= '9'))
    return (subs_search_history(i, param, subs));
  else if (subs[0] == '-')
    return (subs_backsearch_history(i, param, subs, 0));
  else if (subs[0] == '?')
    {
      xsfree(subs);
      subs = get_interrog_subs(param->line, i);
      return (subs_strstr_history(i, param, subs));
    }
  else if (subs[0] == '!')
    return (subs_prev_command(i, param, subs));
  else if (endsubs(subs[0]) == 0)
    return (subs_startstr_history(i, param, subs));
  return (2);
}

int	history_substitution(t_param *param)
{
  int	i;
  char	*subs;
  int	get;

  i = -1;
  while (param->line[++i] != 0)
    {
      if (param->line[i] == '!')
	{
	  subs = get_subs_hist(param->line, i);
	  get = launch_hist(param, subs, i);
	  if (get != 2)
	    return (get);
	}
    }
  return (2);
}
