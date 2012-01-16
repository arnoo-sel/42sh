/*
** history.c for 42sh in /home/farges_y/link/42sh/mysh/src
** 
** Made by yoam farges
** Login   <farges_y@epitech.net>
** 
** Started on  Thu May 22 15:52:19 2008 yoam farges
** Last update Thu Jun 12 14:36:47 2008 yoam farges
*/

#include "42sh.h"

void	init_history(t_param *param)
{
  HIST.history = xsmalloc(sizeof(*(HIST.history)) * (HIST.vhist + 1));
  HIST.time_hist = xsmalloc(sizeof(*(HIST.time_hist)) * (HIST.vhist + 1));
  HIST.nbr_hist = xsmalloc(sizeof(*(HIST.nbr_hist)) * (HIST.vhist + 1));
  HIST.history[HIST.vhist] = NULL;
  HIST.prevsearch = NULL;
  HIST.history[0] = NULL;
  HIST.pos_hist = 0;
  HIST.nb_max_hist = 0;
  if (get_hist_from_file(param) == 1)
    my_printf("Warning: history isn't load.\n");
}

void	do_add_line_in_history(char *line, t_param *param, int number)
{
  if (HIST.history[HIST.pos_hist] != NULL)
    number = (HIST.nbr_hist[HIST.pos_hist] + 1);
  if (HIST.nb_max_hist != 0)
    HIST.pos_hist++;
  if (HIST.pos_hist == HIST.vhist)
    HIST.pos_hist = 0;
  if (HIST.history[HIST.pos_hist] == NULL)
    {
      HIST.history[HIST.pos_hist + 1] = NULL;
      HIST.nb_max_hist++;
    }
  else
    xsfree(HIST.history[HIST.pos_hist]);
  HIST.history[HIST.pos_hist] = my_strdup(line);
  HIST.history[HIST.pos_hist][my_strlen(line)] = 0;
  HIST.nbr_hist[HIST.pos_hist] = number;
}

int	add_line_in_history(char *line, t_param *param, int ttime)
{
  int	number;
  int	stat;

  number = -1;
  stat = 0;
  while (line[++number] != 0)
    if (line[number] != ' ')
      stat = 1;
  if ((stat == 0) || (HIST.vhist == 0))
    return (1);
  number = 1;
  do_add_line_in_history(line, param, number);
  if (ttime == 0)
    HIST.time_hist[HIST.pos_hist] = time(0);
  else
    HIST.time_hist[HIST.pos_hist] = ttime;
  return (0);
}

int	search_back_in_history(t_param *param, int nbr)
{
  int	pos;
  int	count;

  if ((nbr > HIST.nb_max_hist) || (nbr <= 0))
    return (-1);
  pos = HIST.pos_hist;
  count = 0;
  while (count != (nbr - 1))
    {
      pos--;
      if (pos == -1)
	pos = (HIST.vhist - 1);
      count++;
    }
  return (pos);
}

int	search_nbr_history(t_param *param, int nbr)
{
  int	pos;

  pos = 0;
  while (HIST.history[pos] != NULL)
    {
      if (HIST.nbr_hist[pos] == nbr)
	return (pos);
      pos++;
    }
  return (-1);
}
