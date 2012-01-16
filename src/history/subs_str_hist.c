/*
** subs_str_hist.c for 42sh in /home/farges_y/link/42sh/mysh/src/history
** 
** Made by yoam farges
** Login   <farges_y@epitech.net>
** 
** Started on  Sun Jun  1 23:21:26 2008 yoam farges
** Last update Mon Jun  2 01:07:00 2008 yoam farges
*/

#include "42sh.h"

int	subs_startstr_history(int i, t_param *param, char *subs)
{
  int	pos;

  saveprev(param, subs);
  pos = HIST.pos_hist;
  while ((HIST.history[pos] != NULL) && (pos != (HIST.pos_hist + 1)))
    {
      if (my_strncmp(subs, HIST.history[pos], my_strlen(subs)) == 0)
	{
	  mix_str_subs_hist(HIST.history[pos], param, i, my_strlen(subs));
	  xsfree(subs);
	  if ((pos = history_substitution(param)) == 2)
	    return (0);
	  return (pos);
	}
      pos--;
      if (pos == -1)
	pos = (HIST.vhist - 1);
    }
  my_printf("%s: Event not found.\n", subs);
  subs[0] = 0;
  mix_str_subs_hist(subs, param, i, 0);
  xsfree(subs);
  return (1);
}

int	do_prev_search(int i, t_param *param, char *subs)
{
  if (HIST.prevsearch == NULL)
    my_printf("No prev search.\n");
  else
    {
      xsfree(subs);
      subs = my_strdup(HIST.prevsearch);
      return (launch_hist(param, subs, i));
    }
  return (1);
}

int	subs_strstr_history(int i, t_param *param, char *subs)
{
  int	pos;

  if (my_strlen(subs) == 0)
    return (do_prev_search(i, param, subs));
  saveprev(param, subs);
  pos = HIST.pos_hist;
  while ((HIST.history[pos] != NULL) && (pos != (HIST.pos_hist + 1)))
    {
      if (my_strstr(HIST.history[pos], subs) != NULL)
	{
	  mix_str_subs_hist(HIST.history[pos], param, i, my_strlen(subs));
	  xsfree(subs);
	  if ((pos = history_substitution(param)) == 2)
	    return (0);
	  return (pos);
	}
      pos--;
      if (pos == -1)
	pos = (HIST.vhist - 1);
    }
  my_printf("%s: Event not found.\n", subs);
  subs[0] = 0;
  mix_str_subs_hist(subs, param, i, 0);
  xsfree(subs);
  return (1);
}
