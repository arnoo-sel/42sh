/*
** history_aff.c for 42sh in /home/farges_y/cunix/42sh/mysh
** 
** Made by yoam farges
** Login   <farges_y@epitech.net>
** 
** Started on  Wed May 28 14:14:32 2008 yoam farges
** Last update Mon Jun  2 04:41:12 2008 yoam farges
*/

#include "42sh.h"

void	aff_hist_fbsd(int pos, t_param *param)
{
  char	*time;

  time = NULL;
  param = param;
  pos = pos;
#if (OS == BSD)
  time = ctime(&(HIST.time_hist[pos]));
  time[16] = 0;
  my_printf("\t%d\t%s\t%s\n", HIST.nbr_hist[pos],
	    (time + 11), HIST.history[pos]);
#endif
}

int	b_history(t_param *param, char **cmd)
{
  int	pos;
  int	count;

  count = 0;
  cmd = cmd;
  pos = HIST.pos_hist;
  while (count != HIST.nb_max_hist)
    {
      pos++;
      if (HIST.history[pos] == NULL)
	pos = 0;
#if (OS == BSD)
      aff_hist_fbsd(pos, param);
#elif (OS == NUX)
      my_printf("\t%d\t%d\t%s\n", HIST.nbr_hist[pos],
		HIST.time_hist[pos], HIST.history[pos]);
#endif
      count++;
    }
  return (0);
}
